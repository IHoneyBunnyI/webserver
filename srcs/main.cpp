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
	
	Parser parser(configFile);
	parser.parseConfig(); // MARIA
	// create all Servers
	// Server.ports = std::vector<int> ports // пример
	// Server.ports = Parser.getPorts()
	// Server.locations = Parser.getLocations()
	// Server.roots = Parser.getRoots()
	// create all Servers

	Server server;
	//server.setPorts(parser.getPorts());
	//server.AddPort(8080); //можно добавлять нужные Порты
	server.AddPort(8090);
	server.Start();
}
