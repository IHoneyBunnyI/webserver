#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include "webserv.hpp"
#include <fstream>

int compress_array(pollfd *fds, int &nfds)
{
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
	return 1;
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

int fatal(void)
{
	std::cout << "Error argument!" << std::endl;
	return 2;
}
