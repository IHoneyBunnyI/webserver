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

	//идея заключается в том, чтобы парсер брал все данные о серверах (а их может быть любое кол-во)
	//Server со всеми данными, где будет вектор портов, location'ов и т.д.
	//поэтому было принято решение вынести класс Parser из поля класса Server,
	//далее внутри класса Server будет поле класса HttpRequest, который уже будет парсить каждый запрос отдельно
	
	Parser config(configFile);
	try {
		config.ParseConfig();
	} catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
		return 1;
	}

	Server server(config);
	server.CreateListenSockets();
	server.Start();
}
