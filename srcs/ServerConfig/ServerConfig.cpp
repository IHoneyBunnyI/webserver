#include "ServerConfig.hpp"

ServerConfig::ServerConfig():
	server_names(),
	client_max_body_size(0),
	ips(),
	ports(),
	locations(),
	error_pages(),
	autoindex(0)
{}

ErrorPage::ErrorPage():
	errors(),
	error_page("")
{}

Location::Location():
	location(""),
	root(""),
	alias(""),
	method(""),
	index(""),
	cgi_path(""),
	cgi_extensions(""),
	upload_pass("")
{}
