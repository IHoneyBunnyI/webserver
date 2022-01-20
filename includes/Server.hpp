#ifndef SERVER_HPP
#define SERVER_HPP
#include "Parser.hpp"

#include <iostream>

#define SERVER_PORT 2121

class Server
{

public:
	Server();
	Server(std::string);
	~Server();
	Server(const Server& ref);
	Server& operator = (const Server& ref);

	void parseConfig();
	void start();
	Parser getParser();

private:
	Parser parser;
};

#endif
