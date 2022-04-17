#include "ServerConfig.hpp"

ServerConfig::ServerConfig():
	server_names(),
	client_max_body_size(0),
	ips(),
	ports(),
	root("html"),
	locations(),
	error_pages(),
	autoindex(0),
	listenExist(0),
	client_max_body_sizeExist(0),
	autoindexExist(0),
	rootExist(0),
	sockets(0),
	fds(0)
{
	ips.push_back("0.0.0.0");
	ports.push_back(80);
}

ErrorPage::ErrorPage():
	errors(),
	error_page("")
{}

Location::Location():
	location(""),
	root("html"),
	alias(""),
	methods(),
	indexes(),
	cgi_path(""),
	cgi_extensions(),
	upload_pass(""),
	rootExist(0),
	aliasExist(0),
	methodsExist(0),
	cgi_pathExist(0),
	cgi_extensionsExist(0),
	upload_passExist(0),
	indexExist(0)
{
	this->indexes.push_back("index");
	this->indexes.push_back("index.html");
	this->methods.push_back("GET");
}

std::ostream& operator << (std::ostream& cout, const ServerConfig& c)
{
	cout << "{\n\tserver_names :";
	for (unsigned int i = 0; i < c.server_names.size(); i++)
		cout << " " << c.server_names[i];
	//cout << "}";
	cout << "\n\tclient_max_body_size: " << c.client_max_body_size;
	cout << "\n\tips:";
	for (unsigned int i = 0; i < c.ips.size(); i++)
		cout << " " << c.ips[i];
	cout << "\n\tports:";
	for (unsigned int i = 0; i < c.ports.size(); i++)
		cout << " " << c.ports[i];

	cout << "\n\troot: " << c.root;
	cout << "\n\tautoindex: " << (int)c.autoindex;
	for (unsigned int i = 0; i < c.locations.size(); i++) {
		cout << "\n\tlocation: {";
		cout << "\n\t\tlocation: " << c.locations[i].location;
		cout << "\n\t\troot: " << c.locations[i].root;
		cout << "\n\t\talias: " << c.locations[i].alias;
		cout << "\n\t\tmethods:";
		for (unsigned int j = 0; j < c.locations[i].methods.size(); j++) {
			cout << " " + c.locations[i].methods[j];
		}
		cout << "\n\t\tindex:";
		for (unsigned int j = 0; j < c.locations[i].indexes.size(); j++) {
			cout << " " + c.locations[i].indexes[j];
		}
		cout << "\n\t\tcgi_path: " << c.locations[i].cgi_path;
		cout << "\n\t\tcgi_extensions:";
		for (unsigned int j = 0; j < c.locations[i].cgi_extensions.size(); j++) {
			cout << " " + c.locations[i].cgi_extensions[j];
		}
		cout << "\n\t\tupload_pass: " << c.locations[i].upload_pass;
		cout << "\n\t}";
	}
	for (unsigned int i = 0; i < c.error_pages.size(); i++) {
		cout << "\n\terror page: {\n\t\terrors:";
		for (unsigned int j = 0; j < c.error_pages[i].errors.size(); j++) {
			cout <<  " " << c.error_pages[i].errors[j];
		}
		cout << "\n\t\tpage: " << c.error_pages[i].error_page;
		cout << "\n\t}";
	}
	cout << "\n}";
	return (cout);
}
