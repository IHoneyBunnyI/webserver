#include "Server.hpp"

Server::Server() {std::cout << "A'm SERVER" <<std::endl;port =10;}
Server::~Server() {}
Server::Server(const Server& ref) {(void)ref;}

Server& Server::operator = (const Server& ref)
{
	(void)ref;
	return *this;
}
