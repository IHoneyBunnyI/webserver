#include <iostream>
#include <fstream>
#include <vector>
#include "Server.hpp"
#include "Parser.hpp"
#include "webserv.hpp"

void log(std::string message)
{
	std::ofstream logfile("logs.webserv", std::ios::app | std::ios::ate);
	if (!logfile)
	{
		std::cout << "error open logs.webserv!" << std::endl;
		exit (1);
	}

	std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();
	time_t	tt = std::chrono::system_clock::to_time_t(time_point);
	tm local_tm = *localtime(&tt);

	logfile << std::put_time(&local_tm, "[%H:%M:%S %d-%m-%Y] ");
	logfile << message << std::endl;

	logfile.close();
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
	server.addPort(8080);
	server.addPort(8090);
	server.start(); // POGNALI
}
