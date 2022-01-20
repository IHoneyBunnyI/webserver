#include <iostream>
#include "utils.hpp"
#include "Server.hpp"

int main(int argc, char** av)
{
	std::string configFile = "webserv.conf";
	if (argc != 1 && argc != 2)
		return (argc_error());
	if (argc == 2)
		configFile = av[1];
	Server server(configFile);
	server.getParser().parseConfig(); // MARIA
	server.start(); // POGNALI
}
