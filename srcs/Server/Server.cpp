#include <fstream>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Server.hpp"
#include "webserv.hpp"

Server::Server(): ports(0), sockets(0), request("") {}
Server::~Server() {}

Server::Server(const Server& ref)
{
	this->ports = ref.ports;
	this->request = ref.request;
}

Server& Server::operator = (const Server& ref)
{
	if (this != &ref)
	{
		this->ports = ref.ports;
		this->request = ref.request;
	}
	return *this;
}

void Server::setPorts(std::vector<int> ports)
{
	this->ports = ports;
}

void Server::addPort(int port)
{
	this->ports.push_back(port);
}

std::vector<int> Server::getPort()
{
	return (this->ports);
}

void Server::openConnection(pollfd *fds, int &nfds, int i)
{
	int new_sd = 0;
	while (new_sd != -1)
	{
		new_sd = accept(fds[i].fd, 0, 0); // тут на счет 1 параметра не уверен до конца
		if (new_sd < 0)
			break;
		std::cout << GREEN "New connection" WHITE << std::endl;
		fds[nfds].fd = new_sd;
		fds[nfds].events = POLLIN;
		nfds++;
	}
}

int Server::closeConnection(int &close_connect, pollfd *fds, int i)
{
		std::cout << RED"Close connection with fd: " << fds[i].fd << WHITE << std::endl;
		close_connect = 0;
		close(fds[i].fd);
		fds[i].fd = -1;
		return 1;
}
