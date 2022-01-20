#include <iostream>
#include "utils.hpp"
#include "Server.hpp"

#define SERVER_PORT 8080

int main(int argc, char** av)
{
	std::string configFile = "webserv.conf";
	if (argc != 1 && argc != 2)
		return (argc_error());
	if (argc == 2)
		configFile = av[1];
	Server server(configFile);
	server.parseConfig();
	server.start();
}
