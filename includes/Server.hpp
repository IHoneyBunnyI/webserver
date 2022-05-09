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
	void CreateServerSockets();
	void CloseConnection(std::vector<pollfd> &fds, int i);
	void OpenConnection(ServerConfig &server, int i);

private:
	std::vector<ServerConfig> servers;
	std::map<int, std::string> fd_ip; //в будущем для печенья (cookies)
};

#endif
