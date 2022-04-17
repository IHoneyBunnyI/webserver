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
	std::vector<ServerConfig> getServers();
	void ParseConfig();
	static void trim(std::string &src);
	static std::vector<std::string> split(const std::string& str, const std::string& delimeter);
	static void getLine(std::ifstream &stream, std::string &line);
	static void replace_all(std::string& inout, std::string_view what, std::string_view with);

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

	class DirectiveDuplicate: public std::exception
	{ public:	const char *what() const throw();
				DirectiveDuplicate(std::string s) throw();
				~DirectiveDuplicate() throw();
				std::string directive; };


	class RootDuplicateAliasExists: public std::exception
	{ public:	const char *what() const throw(); };

	class AliasDuplicateRootExists: public std::exception
	{ public:	const char *what() const throw(); };

private:
	static unsigned int numLine;
	static std::string configFile;
	std::vector<ServerConfig> servers;
};

ServerConfig ParseServer(std::ifstream &stream);
void Listen(ServerConfig &server, std::string line);
void ServerName(ServerConfig &server, std::string line);
void MaxBodySize(ServerConfig &server, std::string line);
void ErrorPage(ServerConfig &server, std::string line);
void Autoindex(ServerConfig &server, std::string line);
void ServerRoot(ServerConfig &server, std::string line);
void ParseLocation(std::ifstream &stream, ServerConfig &server, std::string line);
void LocationRoot(Location &location, std::string line);
void Alias(Location &location, std::string line);
void Method(Location &location, std::string line);
void CgiPath(Location &location, std::string line);
void CgiExtensions(Location &location, std::string line);
void UploadPass(Location &location, std::string line);
void Index(Location &location, std::string line);

#endif
