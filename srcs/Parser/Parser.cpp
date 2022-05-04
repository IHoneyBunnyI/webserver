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

std::vector<ServerConfig> Parser::getServers() {
	return (this->servers);
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
	for (uint i = 0; i < res.size(); i++) {
		Parser::trim(res[i]);
	}
	return (res);
}

void Parser::getLine(std::ifstream &stream, std::string &line) {
	std::getline(stream, line);
	numLine++;
}

void Parser::replace_all(std::string& inout, std::string_view what, std::string_view with)
{
	for (std::string::size_type pos = 0; inout.npos != (pos = inout.find(what.data(), pos, what.length())); pos += with.length()) {
		inout.replace(pos, what.length(), with.data(), with.length());
	}
}

const char *Parser::FileNotOpen::what() const throw() {
	return ("Error open config file");
}

const char *Parser::InvalidNumberOfArgument::what() const throw() {
	std::string *error = new(std::string)("invalid number of arguments in " + Parser::configFile + ":" + std::to_string(Parser::numLine));
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

const char *Parser::AliasDuplicateRootExists::what() const throw() {
	std::string *error = new(std::string)("\"alias\" directive is duplicate, \"root\" directive was specified earlier in " + Parser::configFile + ":" + std::to_string(Parser::numLine));
	return (error->c_str());
}

const char *Parser::RootDuplicateAliasExists::what() const throw() {
	std::string *error = new(std::string)("\"root\" directive is duplicate, \"alias\" directive was specified earlier in " + Parser::configFile + ":" + std::to_string(Parser::numLine));
	return (error->c_str());
}

Parser::DirectiveDuplicate::~DirectiveDuplicate() throw(){}
Parser::DirectiveDuplicate::DirectiveDuplicate(std::string s) throw(): directive(s){}
const char *Parser::DirectiveDuplicate::what() const throw() {
	std::string *error = new(std::string)("\"" + this->directive + "\" directive is duplicate in " + Parser::configFile + ":" + std::to_string(Parser::numLine));
	return (error->c_str());
}
