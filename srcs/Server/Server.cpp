#include "Server.hpp"
#include "webserv.hpp"

Server::Server():
	servers(0),
	fd_ip()
{}

Server::~Server() {}

Server::Server(Parser &parser):
	servers(parser.getServers()),
	fd_ip() {
	//for (unsigned int i = 0; i < servers.size(); i++) {
		//std::cout << servers[i];
	//}
}

Server::Server(const Server& ref) {
	this->servers = ref.servers;
	this->fd_ip = ref.fd_ip;
}

Server& Server::operator = (const Server& ref) {
	if (this != &ref) {
		this->servers = ref.servers;
		this->fd_ip = ref.fd_ip;
	}
	return *this;
}
