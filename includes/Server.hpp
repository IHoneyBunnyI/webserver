#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>

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

private:
	std::string configFile;

};

#endif
