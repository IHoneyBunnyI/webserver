#include <iostream>
#include "Parser.hpp"
#include <fstream>

Parser::Parser() {}
Parser::~Parser() {}
Parser::Parser(const Parser& ref)
{
	this->configFile = ref.configFile;
}
Parser& Parser::operator = (const Parser& ref)
{
	if (this != &ref)
	{
		this->configFile = ref.configFile;
	}
	return *this;
}

void Parser::setConfigFile(std::string conf)
{
	this->configFile = conf;
}

void Parser::parseConfig()
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
