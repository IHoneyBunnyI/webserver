#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include "Server.hpp"
#include "webserv.hpp"

std::string get_path_from_GET(std::string request) // временный костыль
{
	std::string::iterator begin = request.begin() + (request.find("/"));
	std::string::iterator end = request.begin() + request.find(" ", request.find("/")) ;
	std::string res(begin, end);
	return res;
}

int create_listen_socket(int port)
{
	struct sockaddr_in socket_in;

	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)
	{
		log("socket not created");
		exit(1);
	}
	log("Socket create");

	int on = 1;
	if ((setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0) //Разрешаем многократное использование дескриптора сокета
	{
		log("setsockopt() error");
		close(sock_fd);
		exit(1);
	}

	if ((fcntl(sock_fd, F_SETFL, O_NONBLOCK)) < 0) //Делаем сокет не блокирующим
	{
		log("fcntl() error");
		close(sock_fd);
		exit(1);
	}

	memset(&socket_in, 0, sizeof(socket_in));
	socket_in.sin_family = PF_INET;
	socket_in.sin_port = htons(port); //Задаем порт, который будем слушать
	socket_in.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP

	if (bind(sock_fd, (const struct sockaddr *)&socket_in, sizeof(socket_in)) < 0) // связываем сокет с именем ??
	{
		log("bind() error");
		close(sock_fd);
		exit(1);
	}

	if ((listen(sock_fd, 1024)) < 0) //Слушаем сокет
	{
		log("listen() error");
		close(sock_fd);
		exit(1);
	}
	return (sock_fd);
}

void Server::start()
{
	log("Start Server");

	int sock_fd = create_listen_socket(this->port);


	pollfd fds[100];
	int nfds = 1;
	memset(fds, 0 , sizeof(fds));
	fds[0].fd = sock_fd;
	fds[0].events = POLLIN;

	int close_connect = 0;
	int compress_array = 0;
	int rpoll = 0;
	while (1)
	{
		std::cout << "Poll()" << std::endl;
		rpoll = poll(fds, nfds, -1);
		std::cout << "rpoll = " << rpoll << std::endl;
		if (rpoll < 0)
		{
			std::cout << "Poll() error" << std::endl;
			continue;
		}
		if (rpoll == 0)
		{
			std:: cout << "Poll() timeout" << std::endl;
			continue;
		}
		
		int current_size = nfds;
		std::cout << "current_size = " << current_size << std::endl;
		for (int i = 0; i < current_size; i++)
		{
			if (fds[i].revents == 0)
				continue;
			else if (fds[i].fd == sock_fd)
			{
				int new_sd = 0;
				while (new_sd != -1)
				{
					new_sd = accept(sock_fd, 0, 0);
					if (new_sd < 0)
						break;
					std::cout << GREEN "New connection" WHITE << std::endl;
					fds[nfds].fd = new_sd;
					fds[nfds].events = POLLIN;
					nfds++;
				}
			}
			else
			{
				char buffer[1000];
				memset(buffer, 0, 1000);
				std::cout << "Descriptor to read=\t" <<  fds[i].fd << std::endl;
				close_connect = 0;
				while (1)
				{
					int rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
					if (rc < 0)
					{
						std::cout << YELLOW "full data read" WHITE << std::endl;
						break;
					}
					if (rc == 0)
					{
						std::cout << "Connection closed" << std::endl;
						close_connect = 1;
						break;
					}
					this->request += buffer;
					memset(buffer, 0, 1000);
				}
					std::cout << PURPLE "Request: " << this->request << WHITE;
					std::string path = get_path_from_GET(this->request);

					std::string response =
					"HTTP/1.1 200 OK\r\n"
					"Content-Type: text/html; charset=UTF-8\r\n\r\n"
					"<doctype !html>\n"
					"	<html>\n"
					"		<head>\n"
					"			<title>Webserv</title>\n"
					"			<style>body { background-color: #444 }\n"
					"				   h1 { font-size:4cm; text-align: center; color: black;\n"
					"						text-shadow: 0 0 2mm red}\n"
					"			</style>\n"
					"		</head>\n"
					"<body>\n"
					"		<h1>HELLO, world!</h1>\n"
					"</body>\n"
					"</html>\r\n";

					if ((send(fds[i].fd, response.c_str(), response.length(), 0)) < 0)
					{
						std::cout << "send() failed" << std::endl;
						close_connect = 1;
						break;
					}
					this->request.clear();

				if (close_connect)
				{
					close_connect = 0;
					std::cout << "AAAA" <<std::endl;
					close(fds[i].fd);
					fds[i].fd = -1;
					compress_array = 1;
				}
			}
		}

		if (compress_array)
		{
			std::cout << "AAAAAAA" << std::endl;
			compress_array = 0;
			for (int i = 0; i < nfds; i++)
			{
				if (fds[i].fd == -1)
				{
					for(int j = i; j < nfds-1; j++)
						fds[j].fd = fds[j+1].fd;
					i--;
					nfds--;
				}
			}
		}
		std::cout << RED "===========" WHITE << std::endl;
	}

}
