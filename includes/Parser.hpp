#ifndef PARSER_HPP
#define PARSER_HPP
#include <iostream>

class Parser //FOR MARIA
{
public:
	Parser();
	Parser(std::string);
	~Parser();
	Parser(const Parser& ref);
	Parser& operator = (const Parser& ref);

	void setConfigFile(std::string);
	void parseConfig();
private:
	std::string configFile;
};

#endif
