#include "Parser.hpp"
#include "Server.hpp"

void Parser::ParseConfig()
{
	int problem = 0;
	if (problem)
	{
		Server::Log("ERRROR AAAAA PROBLEM!!!!");
		std::cout << "Error config file!" << std::endl;
	}
	// пишем логи в файл 'logs.webserv', если в файле конфига есть проблемы
}
