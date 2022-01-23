#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include "Server.hpp"
#include "webserv.hpp"

void Server::start()
{
	int rc = 0;

	log("Start Server");
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
	socket_in.sin_port = htons(SERVER_PORT); //Задаем порт, который будем слушать
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

	//int recv(int sockfd, void *buf, int len, int flags); //местный read 
	
	pollfd fds[100];

	memset(fds, 0 , sizeof(fds));

	fds[0].fd = sock_fd;
	fds[0].events = POLLIN;

	int timeout = (10 * 60 * 1000);
	int nfds = 1;

	char buffer[200];

	//MAIN
	while (1)
	{
		//log("Waiting on poll()");
		printf("Waiting on poll()");
		
		rc = poll(fds, nfds, timeout);
		if (rc < 0)
		{
			//log("poll() error");
			printf("poll() error");
			break;
		}
		if (rc == 0)
		{
			printf("poll() timed out");
			break;
		}
		int current_size = nfds;
		for (int i = 0; i < current_size; i++)
		{
			if(fds[i].revents == 0)
				continue;

			if(fds[i].revents != POLLIN)
			{
				//log("Revents error");
				printf("	Error! revents = %d\n", fds[i].revents);
				break;
			}


			if (fds[i].fd == sock_fd)
			{
				printf("Listening socket is readable\n");
				int new_sockfd = 0;
				while (new_sockfd != -1)
				{
					new_sockfd = accept(sock_fd, 0, 0);
					if (new_sockfd < 0)
					{
						printf("AAAAAAAAAAAAAA\n");
						break;
					}
					printf("	New incoming connection - %d\n", new_sockfd);
					fds[nfds].fd = new_sockfd;
					fds[nfds].events = POLLIN;
					nfds++;
				}
			}
			else
			{
				printf("	Descriptor %d is readable\n", fds[i].fd);
				while (1)
				{
					rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
					if (rc < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							//log("	recv() failed");
							printf("	recv() failed");
						}
						break;
					}
					if (rc == 0)
					{
						printf("	Connection closed\n");
						break;
					}

					int len = rc;
					printf("	%d bytes received\n", len);
					printf("\n\n");
					printf("\033[38;5;46m%s\033[0m\n", buffer);
				}
			}
		}


	}
	
	//close(sock_fd);
}
