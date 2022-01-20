#include "Server.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>

void Server::start()
{
	std::ofstream log("logs.webserv", std::ios::app | std::ios::ate);
	if (!log.is_open())
	{
		std::cout << "error open logs.webserv!" << std::endl;
		exit(1);
	}

	struct sockaddr_in socket_in;

	socket_in.sin_family = PF_INET;
	socket_in.sin_port = htons(SERVER_PORT);
	int ip = 127 << 24 | 1; //128.0.0.1 битовое представление
	socket_in.sin_addr.s_addr = htonl(ip);

	int sock_fd;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
}
