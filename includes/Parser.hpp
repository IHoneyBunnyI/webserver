#ifndef PARSER_HPP
#define PARSER_HPP
#include <iostream>
#include <vector>
#include "ServerConfig.hpp"


class Parser //FOR MARIA
{
public:
	Parser();
	Parser(std::string);
	~Parser();
	Parser(const Parser& ref);
	Parser& operator = (const Parser& ref);

	void SetConfigFile(std::string);
	void ParseConfig();
	static void trim(std::string &src);
	static void getLine(std::ifstream &stream, std::string &line);

	class FileNotOpen: public std::exception
	{ public: const char *what() const throw();};

	class OpeningBracketExpected: public std::exception
	{ public: const char *what() const throw(); };


private:
	static unsigned int numLine;
	static std::string configFile;
	std::vector<ServerConfig> servers;
};

#endif
