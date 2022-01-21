#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Server.hpp"
#include "webserv.hpp"

void Server::start()
{
	log("Start Server");
	struct sockaddr_in socket_in;

	socket_in.sin_family = PF_INET;
	socket_in.sin_port = htons(SERVER_PORT);
	int ip = 127 << 24 | 1; //127.0.0.1 битовое представление
	socket_in.sin_addr.s_addr = htonl(ip);

	int sock_fd;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)

	close(sock_fd);
}
