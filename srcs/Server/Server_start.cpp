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
	std::string::iterator end = request.begin() + request.find(" ", request.find("/")); // тут request.find возвраает npos
	if (begin == end)
		std::cout << "AAAAAAAAAAAAAAAAAA" << std::endl;
	std::string res(begin, end); // тут бага если дать через nc что-то с '/' без пробела
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
	socket_in.sin_addr.s_addr = inet_addr("0.0.0.0"); //IP

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

	for (std::vector<int>::iterator begin = this->ports.begin(); begin != this->ports.end(); begin++)
		this->sockets.push_back(create_listen_socket(*begin));

	pollfd fds[1000];
	//int sock_fd = this->sockets[0];
	int nfds = this->sockets.size();
	//int nfds = 1;
	memset(fds, 0 , sizeof(fds));


	int i = 0;
	for (std::vector<int>::iterator begin = this->sockets.begin(); begin != this->sockets.end(); begin++)
	{
		fds[i].fd = *begin;
		fds[i].events = POLLIN;
		i++;
	}

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
		
		unsigned int current_size = nfds;
		//std::cout << "current_size = " << current_size << std::endl;
		for (unsigned int i = 0; i < current_size; i++)
		{
			if (fds[i].revents == 0)
				continue;
			//else if (fds[i].fd == sock_fd)
			else if (std::find(this->sockets.begin(), this->sockets.end(), fds[i].fd) != this->sockets.end())
				openConnection(fds, nfds, i);
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

				//std::cout << PURPLE "Request: " << this->request << WHITE;
				std::string path = get_path_from_GET(this->request);
				if (path == "/")
					path = "/index.html";
				
				std::string html = get_file("./www", path);
				std::string headers = send_http(html);
				std::string response = headers + html;
				std::cout << PURPLE << this->request <<WHITE << std::endl;

				if ((send(fds[i].fd, response.c_str(), response.length(), 0)) < 0)
				{
					std::cout << "send() failed" << std::endl;
					close_connect = 1;
					break;
				}
				this->request.clear();

				if (close_connect)
				{
					compress_array = closeConnection(close_connect, fds, i);
				}
			}
		}

		if (compress_array)
		{
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
