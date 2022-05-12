#include "ServerConfig.hpp"

ServerConfig::ServerConfig():
	server_names(),
	client_max_body_size(0),
	ips(),
	ports(),
	root("html"),
	locations(),
	error_pages(),
	autoindex(false),
	listenExist(false),
	client_max_body_sizeExist(false),
	autoindexExist(false),
	rootExist(false),
	FdSet(0),
	ServerSockets(0),
	Clients(0)
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
	rootExist(false),
	aliasExist(false),
	methodsExist(false),
	cgi_pathExist(false),
	cgi_extensionsExist(false),
	upload_passExist(false),
	indexExist(false)
{
	this->indexes.push_back("index");
	this->indexes.push_back("index.html");
	this->methods.push_back("GET");
}

std::ostream& operator << (std::ostream& cout, const ServerConfig& c)
{
	cout << "{\n\tserver_names :";
	for (uint i = 0; i < c.server_names.size(); i++)
		cout << " " << c.server_names[i];
	//cout << "}";
	cout << "\n\tclient_max_body_size: " << c.client_max_body_size;
	cout << "\n\tips:";
	for (uint i = 0; i < c.ips.size(); i++)
		cout << " " << c.ips[i];
	cout << "\n\tports:";
	for (uint i = 0; i < c.ports.size(); i++)
		cout << " " << c.ports[i];

	cout << "\n\troot: " << c.root;
	cout << "\n\tautoindex: " << (int)c.autoindex;
	for (uint i = 0; i < c.locations.size(); i++) {
		cout << "\n\tlocation: {";
		cout << "\n\t\tlocation: " << c.locations[i].location;
		cout << "\n\t\troot: " << c.locations[i].root;
		cout << "\n\t\talias: " << c.locations[i].alias;
		cout << "\n\t\tmethods:";
		for (uint j = 0; j < c.locations[i].methods.size(); j++) {
			cout << " " + c.locations[i].methods[j];
		}
		cout << "\n\t\tindex:";
		for (uint j = 0; j < c.locations[i].indexes.size(); j++) {
			cout << " " + c.locations[i].indexes[j];
		}
		cout << "\n\t\tcgi_path: " << c.locations[i].cgi_path;
		cout << "\n\t\tcgi_extensions:";
		for (uint j = 0; j < c.locations[i].cgi_extensions.size(); j++) {
			cout << " " + c.locations[i].cgi_extensions[j];
		}
		cout << "\n\t\tupload_pass: " << c.locations[i].upload_pass;
		cout << "\n\t}";
	}
	for (uint i = 0; i < c.error_pages.size(); i++) {
		cout << "\n\terror page: {\n\t\terrors:";
		for (uint j = 0; j < c.error_pages[i].errors.size(); j++) {
			cout <<  " " << c.error_pages[i].errors[j];
		}
		cout << "\n\t\tpage: " << c.error_pages[i].error_page;
		cout << "\n\t}";
	}
	cout << "\n}";
	return (cout);
}
