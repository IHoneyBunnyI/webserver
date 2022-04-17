#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP
#include <iostream>
#include <vector>
#include <poll.h>

struct Location {
	std::string location;
	std::string root;
	std::string alias;
	std::vector<std::string> methods;
	std::vector<std::string> indexes;
	std::string cgi_path;
	std::vector<std::string> cgi_extensions;
	std::string upload_pass;
	unsigned char rootExist;
	unsigned char aliasExist;
	unsigned char methodsExist;
	unsigned char cgi_pathExist;
	unsigned char cgi_extensionsExist;
	unsigned char upload_passExist;
	unsigned char indexExist;

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
	std::string root;
	std::vector<Location> locations;
	std::vector<ErrorPage> error_pages;
	unsigned char autoindex;
	unsigned char listenExist;
	unsigned char client_max_body_sizeExist;
	unsigned char autoindexExist;
	unsigned char rootExist;
	std::vector<int> sockets;
	std::vector<pollfd> fds;

	ServerConfig();
};

std::ostream& operator << (std::ostream& cout, const ServerConfig& fixed);
#endif
