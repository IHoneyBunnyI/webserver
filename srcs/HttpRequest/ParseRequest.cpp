#include "HttpRequest.hpp"
#include "Server.hpp"
#include "webserv.hpp"
#include <sys/socket.h>

void HtppRequest::ParseRequest(int &close_connect, int fd) {
	(void)close_connect;
	(void)fd;
	return;
}
