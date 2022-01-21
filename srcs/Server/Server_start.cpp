#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "Server.hpp"
#include "webserv.hpp"

void Server::start()
{
	log("Start Server");
	struct sockaddr_in socket_in;

	socket_in.sin_family = PF_INET;
	socket_in.sin_port = htons(SERVER_PORT);
	//int ip = 127 << 24 | 1; //127.0.0.1 битовое представление
	//socket_in.sin_addr.s_addr = htonl(ip);
	socket_in.sin_addr.s_addr = inet_addr("127.0.0.1");

	int sock_fd;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0); //
	log("socket create");
	if (sock_fd == -1)
	{
		log("socket not created");
		exit(1);
	}

	if (bind(sock_fd, (const struct sockaddr *)&socket_in, sizeof(socket_in)) < 0)
	{
		log("socket not bind");
		exit(1);
	}

	int fd_lis = listen(sock_fd, 1024);
	if (fd_lis == -1)
	{
		log("can't listen this socket");
		exit(1);
	}

	//int recv(int sockfd, void *buf, int len, int flags);
	
	//close(sock_fd);
}
