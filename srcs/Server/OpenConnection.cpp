#include "Server.hpp"
#include "webserv.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>

void Server::OpenConnection(ServerConfig &server, int i)
{
	struct sockaddr_in in;
	socklen_t len_in = sizeof(in);

	int new_sd = 0;
		new_sd = accept(server.fds[i].fd, (sockaddr *)&in, &len_in); 
		if (new_sd < 0)
			return;
		pollfd fd;
		fd.fd = new_sd;
		fd.events = POLLIN;
		std::cout << GREEN "New connection with fd: " << new_sd << WHITE << std::endl;
		server.fds.push_back(fd);

		char bits[100];
		memset(&bits, 0, sizeof(bits));
		inet_ntop(in.sin_family, &in.sin_addr, bits, sizeof(bits));
		std::string ip(bits);
		Server::Log("Client with ip: " + ip + " and fd: " + std::to_string(new_sd) + " connected");
		this->fd_ip[server.fds[server.fds.size() - 1].fd] = ip;
}
