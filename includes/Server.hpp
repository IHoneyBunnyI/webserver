#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <vector>
#include <map>
#include <poll.h>
#include "Parser.hpp"

class Server
{

public:
	Server();
	~Server();
	Server(const Server& ref);
	Server& operator = (const Server& ref);

	void start();
	void setPorts(std::vector<int> ports);

	void addPort(int port);
	void GET(int fd, int &close_connect, std::string request);
	void POST();
	void DELETE();


private:
	std::vector<int> ports;
	std::vector<int> sockets;
	std::map<int, std::string> fd_ip; //в будущем для печенья (cookies)
	pollfd fds[1000];
};

#endif
