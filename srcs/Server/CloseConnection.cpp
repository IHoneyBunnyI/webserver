#include "Server.hpp"
#include "webserv.hpp"
#include <unistd.h>

void Server::CloseConnection(std::vector<pollfd> &fds, int i)
{
		std::string ip = fd_ip[fds[i].fd];
		Server::Log("Client with ip: " + ip + " and fd: " + std::to_string(fds[i].fd) + " disconnect");
		std::cout << RED "Disconnect with fd: " << fds[i].fd << WHITE << std::endl;
		this->fd_ip.erase(fds[i].fd); // пока не очень понятно зачем, но пусть
		close(fds[i].fd);
		fds[i].fd = -1;
}

