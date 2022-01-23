#include "Server.hpp"
#include <fstream>

Server::Server() {}
Server::~Server() {}

Server::Server(const Server& ref)
{
	this->port = ref.port;
}

Server& Server::operator = (const Server& ref)
{
	if (this != &ref)
	{
		this->port = ref.port;
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
