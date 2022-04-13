#include <iostream>
#include "Parser.hpp"
#include "Server.hpp"
#include "webserv.hpp"
#include <fstream>

std::string Parser::configFile = "webserv.conf";

Parser::Parser() {}

Parser::Parser(std::string conf) {
	Parser::configFile = conf;
	Parser::numLine = 0;
}

Parser::~Parser() {}

Parser::Parser(const Parser& ref)
{
	(void)ref;
	//this->configFile = ref.configFile;
}

Parser& Parser::operator = (const Parser& ref)
{
	if (this != &ref)
	{
		//this->configFile = ref.configFile;
	}
	return *this;
}

void Parser::SetConfigFile(std::string conf)
{
	Parser::configFile = conf;
}

void Parser::trim(std::string &src)
{
	src.erase(std::find_if_not(src.rbegin(), src.rend(), ::isspace).base(), src.end()); 
	src.erase(src.begin(), std::find_if_not(src.begin(), src.end(), ::isspace));
}

void Parser::getLine(std::ifstream &stream, std::string &line) {
	std::getline(stream, line);
	numLine++;
}

const char *Parser::FileNotOpen::what() const throw() {
	return ("Error open config file");
}
const char *Parser::OpeningBracketExpected::what() const throw() {
	std::string *error = new(std::string)("Error: expected { in " + Parser::configFile + ":" + std::to_string(Parser::numLine));
	return (error->c_str());
}
