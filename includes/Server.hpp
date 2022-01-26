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

	void parseConfig();
	void start();
	void setPorts(std::vector<int> ports);
	void addPort(int port);
	std::vector<int> getPort();

	void openConnection(pollfd *fds, int &nfds, int i);
	int closeConnection(int &close_connect, pollfd *fds, int i);


private:
	std::vector<int> ports;
	std::vector<int> sockets;
	std::string request;
	std::map<int, std::string> fd_ip; //в будущем для печенья (cookies)
};

#endif
