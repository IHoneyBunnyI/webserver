#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <vector>
#include "Parser.hpp"

class Server
{

public:
	Server();
	~Server();
	Server(const Server& ref);
	Server& operator = (const Server& ref);

	void parseConfig();
	void start();
	void setPorts(std::vector<int> ports);
	void addPort(int port);
	std::vector<int> getPort();

private:
	std::vector<int> ports;
	std::vector<int> sockets;
	std::string request;
};

#endif
