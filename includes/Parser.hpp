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
	static std::vector<std::string> split(const std::string& str, const std::string& delimeter);
	static void getLine(std::ifstream &stream, std::string &line);

	class FileNotOpen: public std::exception
	{ public:	const char *what() const throw();};

	class OpeningBracketExpected: public std::exception
	{ public:	const char *what() const throw(); };

	class InvalidNumberOfArgument: public std::exception
	{ public:	const char *what() const throw(); };

	class UnknownDirective: public std::exception
	{ public:	const char *what() const throw();
				UnknownDirective(std::string s) throw();
				~UnknownDirective() throw();
				std::string directive; };

	class RootDuplicate: public std::exception
	{ public:	const char *what() const throw(); };

	class AliasDuplicate: public std::exception
	{ public:	const char *what() const throw(); };

	class RootDuplicateAliasExists: public std::exception
	{ public:	const char *what() const throw(); };

	class AliasDuplicateRootExists: public std::exception
	{ public:	const char *what() const throw(); };

	class MethodDuplicate: public std::exception
	{ public:	const char *what() const throw(); };

private:
	static unsigned int numLine;
	static std::string configFile;
	std::vector<ServerConfig> servers;
};

ServerConfig ParseServer(std::ifstream &stream);
void ParseListen(ServerConfig &server, std::string line);
void ParseServerName(ServerConfig &server, std::string line);
void ParseMaxBodySize(ServerConfig &server, std::string line);
void ParseErrorPage(ServerConfig &server, std::string line);
void ParseAutoindex(ServerConfig &server, std::string line);
void ParseLocation(std::ifstream &stream, ServerConfig &server, std::string line);
void ParseRoot(Location &location, std::string line);
void ParseAlias(Location &location, std::string line);
void ParseMethod(Location &location, std::string line);
void ParseCgiPath(Location &location, std::string line);
void ParseCgiExtensions(Location &location, std::string line);
void ParseUploadPass(Location &location, std::string line);

#endif
