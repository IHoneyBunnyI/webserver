#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include "Server.hpp"
#include "webserv.hpp"

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

	int rpoll = 0;
	while (1)
	{
		printf("Poll()\n\n");
		rpoll = poll(fds, nfds, -1);
		if (rpoll < 0)
		{
			printf("Poll() error");
			exit(1);
		}
		if (rpoll == 0)
		{
			printf("Poll() timeout");
			continue;
		}
		
		int current_size = nfds;
		for (int i = 0; i < current_size; i++)
		{
			if (fds[i].revents == 0)
				continue;
			//if (fds[i].revents != POLLIN)
			//{
				//printf("\033[32mERROR!!!\033[0m\n");
				//exit(1);
			//}
			if (fds[i].fd == sock_fd)
			{
				int new_sd = 0;
				while (new_sd != -1)
				{
					new_sd = accept(sock_fd, 0, 0);
					//if (new_sd < 0)
					printf("New connection\n");
					fds[nfds].fd = new_sd;
					fds[nfds].events = POLLIN;
					nfds++;
				}
			}
			else
			{
				char buffer[20];
				printf("Descriptor %d is readable\n", fds[i].fd);
				int rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);

				int len = rc;
				printf("	%d bytes received\n", len);
			}
		}
	}
}
