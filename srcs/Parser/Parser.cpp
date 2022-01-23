#include <iostream>
#include "Parser.hpp"
#include "webserv.hpp"

Parser::Parser() {}
Parser::Parser(std::string conf): configFile(conf) {}
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
	int problem = 0;
	if (problem)
	{
		log("ERRROR AAAAA PROBLEM!!!!");
		std::cout << "Error config file!" << std::endl;
	}
	// пишем логи в файл 'logs.webserv', если в файле конфига есть проблемы
}
