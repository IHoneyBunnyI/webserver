#include <iostream>
#include <vector>
#include "Server.hpp"
#include "Parser.hpp"
#include "webserv.hpp"
#include <fstream>

int fatal(void)
{
	std::cout << "Error argument!" << std::endl;
	return 2;
}

int main(int argc, char** av)
{
	std::string configFile = "webserv.conf";
	if (argc != 1 && argc != 2)
		return (fatal());
	if (argc == 2)
		configFile = av[1];

	Parser config(configFile);
	try {
		config.ParseConfig();
	} catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
		return 1;
	}

	Server server(config);
	server.CreateServerSockets();
	server.Start();
	std::cout << "END" << std::endl;
}
