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

	//void SetHostPort(std::vector<HostPort> ports);
	void AddPort(int port);
	void AddIp(std::string ip);
	void AddIpPort(std::string ip, int port);
	static void Log(std::string message);
	void Start();
	void GET(int fd, int &close_connect, std::string request);
	void POST();
	void DELETE();


private:
	std::vector<ServerConfig> servers;
	std::vector<pollfd> fds;
	std::map<int, std::string> fd_ip; //в будущем для печенья (cookies)
};

#endif
