#include "Server.hpp"
#include <fstream>

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

