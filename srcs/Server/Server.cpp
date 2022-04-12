#include "Server.hpp"
#include "webserv.hpp"

Server::Server(): listen(0), sockets(0), fd_ip() {}
Server::~Server() {}

Server::Server(const Server& ref)
{
	this->listen = ref.listen;
	this->sockets = ref.sockets;
	this->fd_ip = ref.fd_ip;
}

Server& Server::operator = (const Server& ref)
{
	if (this != &ref)
	{
		this->listen = ref.listen;
		this->sockets = ref.sockets;
		this->fd_ip = ref.fd_ip;
	}
	return *this;
}

void Server::AddPort(int port)
{
	this->listen.push_back((HostPort){"0.0.0.0", port});
}

void Server::AddIp(std::string ip)
{
	this->listen.push_back((HostPort){ip, 80});
}

void Server::AddIpPort(std::string ip, int port) {
	this->listen.push_back((HostPort){ip, port});
}
