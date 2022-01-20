#include <iostream>
#include "Server.hpp"
#include <fstream>

void Server::parseConfig()
{
	std::ofstream log("logs.webserv");
	if (!log)
	{
		std::cout << "error create logs.webserv!" << std::endl;
		exit (1);
	}
	log << "PARSING!" << std::endl;

	int problem = 0;
	if (problem)
	{
		log << "ERRROR AAAAA PROBLEM!!!!" << std::endl;
		std::cout << "Error config file!" << std::endl;
	}
	// пишем логи в файл 'logs.webserv', если в файле конфига есть проблемы
}
