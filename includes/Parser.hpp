#ifndef PARSER_HPP
#define PARSER_HPP
#include <iostream>
#include <vector>

struct Location {
	std::string location;
	std::string root;
	std::string alias;
	std::string method;
	std::string index;
	std::string cgi_path;
	std::string cgi_extensions;
	std::string upload_pass;
};

struct ErrorPage {
	std::vector<int> errors;
	std::string error_page;
};

struct ServerConf {
	std::string server_name;
	int client_max_body_size;
	std::string ip;
	int port;
	std::vector<Location> locations;
	std::vector<ErrorPage> error_pages;
	int autoindex;
};

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
private:
	std::string configFile;
};

#endif
