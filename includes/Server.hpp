#ifndef SERVER_HPP
#define SERVER_HPP
#include "Parser.hpp"

#include <iostream>

#define SERVER_PORT 8080


class Server
{

public:
	Server();
	~Server();
	Server(const Server& ref);
	Server& operator = (const Server& ref);

	void parseConfig();
	void start();
	void setPort(int port);
	int getPort();

private:
	int port;
	std::string request;
};

#endif
