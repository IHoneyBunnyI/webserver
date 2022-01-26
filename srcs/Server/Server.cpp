#include "Server.hpp"
#include <fstream>

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
