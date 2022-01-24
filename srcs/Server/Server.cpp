#include "Server.hpp"
#include <fstream>

Server::Server(): port(0), request("") {}
Server::~Server() {}

Server::Server(const Server& ref)
{
	this->port = ref.port;
	this->request = ref.request;
}

Server& Server::operator = (const Server& ref)
{
	if (this != &ref)
	{
		this->port = ref.port;
		this->request = ref.request;
	}
	return *this;
}

void Server::setPort(int port)
{
	this->port = port;
}

int Server::getPort()
{
	return (this->port);
}
