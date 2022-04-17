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
	Server(Parser &parser);
	Server& operator = (const Server& ref);

	static void Log(std::string message);
	void Start();
	void CreateListenSockets();
	void GET(int fd, int &close_connect, std::string request);
	void POST();
	void DELETE();


private:
	std::vector<ServerConfig> servers;
	//std::vector<pollfd> fds;
	std::map<int, std::string> fd_ip; //в будущем для печенья (cookies)
};

#endif
