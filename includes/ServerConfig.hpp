#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP
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
	char autoindex;

	ServerConfig();
};

#endif
