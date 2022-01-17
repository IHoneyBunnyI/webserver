#include "Server.hpp"

Server::Server() {}
Server::~Server() {}
Server::Server(const Server& ref) {(void)ref;}

Server& Server::operator = (const Server& ref)
{
	(void)ref;
	return *this;
}
