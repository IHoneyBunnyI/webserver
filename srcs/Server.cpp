#include "Server.hpp"
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 2121

Server::Server() {}
Server::~Server() {}
Server::Server(std::string conf)
{
	parser.setConfigFile(conf);
}
Server::Server(const Server& ref)
{
	(void)ref;
	//this->pathConfigFile = ref.pathConfigFile;
}

Server& Server::operator = (const Server& ref)
{
	if (this != &ref)
	{
		//this->pathConfigFile = ref.pathConfigFile;
	}
	return *this;
}

Parser Server::getParser()
{
	return this->parser;
}

void Server::start()
{
	struct sockaddr_in socket;

	socket.sin_family = PF_INET;
	socket.sin_port = htons(SERVER_PORT);
	//socket.sin_addr = htonl();
}
