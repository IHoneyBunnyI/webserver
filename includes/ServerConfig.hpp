#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP
#include <iostream>
#include <vector>
#include <poll.h>

struct Location {
	Location();

	std::string location;
	std::string root;
	std::string alias;
	std::vector<std::string> methods;
	std::vector<std::string> indexes;
	std::string cgi_path;
	std::vector<std::string> cgi_extensions;
	std::string upload_pass;
	bool rootExist;
	bool aliasExist;
	bool methodsExist;
	bool cgi_pathExist;
	bool cgi_extensionsExist;
	bool upload_passExist;
	bool indexExist;
};

struct ErrorPage {
	std::vector<int> errors;
	std::string error_page;

	ErrorPage();
};

struct ServerConfig {
	std::vector<std::string> server_names;
	uint client_max_body_size;
	std::vector<std::string> ips;
	std::vector<int> ports;
	std::string root;
	std::vector<Location> locations;
	std::vector<ErrorPage> error_pages;
	bool autoindex;
	bool listenExist;
	bool client_max_body_sizeExist;
	bool autoindexExist;
	bool rootExist;
	std::vector<int> sockets;
	std::vector<pollfd> fds;

	ServerConfig();
};

std::ostream& operator << (std::ostream& cout, const ServerConfig& fixed);
#endif
