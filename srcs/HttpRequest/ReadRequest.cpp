#include "HttpRequest.hpp"
#include "Server.hpp"
#include "webserv.hpp"
#include <sstream>
#include <sys/socket.h>
#define BUFSIZE (1 << 20)

std::string HttpRequest::ReadRequest(int fd) {
	char buf[BUFSIZE + 1];
	std::memset(buf, 0, BUFSIZE + 1);
	int ret = recv(fd, buf, BUFSIZE, 0);
	std::cout << ret << std::endl;
	if (ret == 0) { //соединение отключено на стороне клиента
		return "";
	}
	return "";
}
