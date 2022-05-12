#include "HttpRequest.hpp"
#include "Server.hpp"
#include "webserv.hpp"
#include <sstream>
#include <sys/socket.h>

void HttpRequest::ReadBody(int fd) {
	(void)fd;
	std::cout << "READBODY" << std::endl;
	return;
}
