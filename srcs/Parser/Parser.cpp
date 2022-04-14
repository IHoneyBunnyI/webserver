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

std::vector<std::string> Parser::split(const std::string& str, const std::string& delimeter)
{
	std::vector<std::string> res;
	size_t prev = 0, pos = str.find(delimeter, prev);

	while ((pos < str.length()) && (prev < str.length())) {
		if (pos == std::string::npos)
			pos = str.length();
		std::string item = str.substr(prev, pos - prev);
		if (!item.empty())
			res.push_back(item);
		prev = pos + delimeter.length();
		pos = str.find(delimeter, prev);
	}
	if (str.size() != prev)
		res.push_back(str.substr(prev, pos - prev));
	return (res);
}

void Parser::getLine(std::ifstream &stream, std::string &line) {
	std::getline(stream, line);
	numLine++;
}

const char *Parser::FileNotOpen::what() const throw() {
	return ("Error open config file");
}

const char *Parser::ToManyArgumentsInDirective::what() const throw() {
	std::string *error = new(std::string)("Syntax Error: to many arguments in directive in " + Parser::configFile + ":" + std::to_string(Parser::numLine));
	return (error->c_str());
}

const char *Parser::OpeningBracketExpected::what() const throw() {
	std::string *error = new(std::string)("Syntax Error: expected { in " + Parser::configFile + ":" + std::to_string(Parser::numLine));
	return (error->c_str());
}

Parser::UnknownDirective::UnknownDirective(std::string s) throw(): directive(s){}
Parser::UnknownDirective::~UnknownDirective() throw(){}

const char *Parser::UnknownDirective::what() const throw() {
	std::string *error = new(std::string)("Syntax Error: unknown directive \'" + this->directive + "\' in " + Parser::configFile + ":" + std::to_string(Parser::numLine));
	return (error->c_str());
}
