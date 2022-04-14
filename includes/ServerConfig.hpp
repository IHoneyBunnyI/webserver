#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP
#include <iostream>
#include <vector>

struct Location {
	std::string location;
	std::string root;
	std::string alias;
	std::vector<std::string> methods;
	std::vector<std::string> indexes;
	std::string cgi_path;
	std::vector<std::string> cgi_extensions;
	std::string upload_pass;
	unsigned char defaultIndexes;
	unsigned char defaultMethods;

	Location();
};

struct ErrorPage {
	std::vector<int> errors;
	std::string error_page;

	ErrorPage();
};

struct ServerConfig {
	std::vector<std::string> server_names;
	unsigned int client_max_body_size;
	std::vector<std::string> ips;
	std::vector<int> ports;
	std::vector<Location> locations;
	std::vector<ErrorPage> error_pages;
	unsigned char autoindex;
	unsigned char defaultListen;

	ServerConfig();
};

std::ostream& operator << (std::ostream& cout, const ServerConfig& fixed);
#endif
