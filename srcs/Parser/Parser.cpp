#include <iostream>
#include "Parser.hpp"
#include "Server.hpp"
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

void Parser::SetConfigFile(std::string conf)
{
	this->configFile = conf;
}
