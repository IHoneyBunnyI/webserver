#include "Server.hpp"
#include "webserv.hpp"

Server::Server():
	//sockets(0),
	fd_ip()
{}

Server::~Server() {}

Server::Server(Parser &parser):
	servers(parser.getServers())
{
	for (unsigned int i = 0; i < servers.size(); i++) {
		std::cout << servers[i];
	}
}
Server::Server(const Server& ref) {
	//this->sockets = ref.sockets;
	this->fd_ip = ref.fd_ip;
}

Server& Server::operator = (const Server& ref) {
	if (this != &ref) {
		//this->sockets = ref.sockets;
		this->fd_ip = ref.fd_ip;
	}
	return *this;
}
