#include "Server.hpp"
#include "webserv.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

void Server::OpenConnection(ServerConfig &server, pollfd *ServerFd)
{
	ServerFd->revents &= ~POLLIN;
	struct sockaddr_in in;
	socklen_t len_in = sizeof(in);

	int new_sd = 0;
	new_sd = accept(ServerFd->fd, (sockaddr *)&in, &len_in); 
	if (new_sd < 0)
		return;
	fcntl(new_sd, F_SETFL, O_NONBLOCK);
	pollfd fd;
	fd.fd = new_sd;
	fd.events = POLLIN;
	server.FdSet.push_back(fd);
	server.ClientSockets.push_back(&(server.FdSet.back()));
	std::cout << GREEN "New connection with fd: " << new_sd << WHITE << std::endl;

	char bits[100];
	memset(&bits, 0, sizeof(bits));
	inet_ntop(in.sin_family, &in.sin_addr, bits, sizeof(bits));
	std::string ip(bits);
	Server::Log("Client with ip: " + ip + " and fd: " + std::to_string(new_sd) + " connected");
	this->fd_ip[server.FdSet.back().fd] = ip;
}
