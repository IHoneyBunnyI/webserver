#include "Server.hpp"
#include "webserv.hpp"

Server::Server(): ports(0), sockets(0), fd_ip() {}
Server::~Server() {}

Server::Server(const Server& ref)
{
	this->ports = ref.ports;
	this->sockets = ref.sockets;
	this->fd_ip = ref.fd_ip;
}

Server& Server::operator = (const Server& ref)
{
	if (this != &ref)
	{
		this->ports = ref.ports;
		this->sockets = ref.sockets;
		this->fd_ip = ref.fd_ip;
	}
	return *this;
}

void Server::SetPorts(std::vector<int> ports)
{
	this->ports = ports;
}

void Server::AddPort(int port)
{
	this->ports.push_back(port);
}
