#include "HttpRequest.hpp"
#include "Server.hpp"
#include "webserv.hpp"
#include <sstream>
#include <sys/socket.h>
#define BUFSIZE (1 << 20)

int HttpRequest::ReadRequest(std::string &line, int fd) {
	static std::string cache;
	char buf[BUFSIZE + 1];
	int rc = 1;
	std::memset(buf, 0, BUFSIZE + 1);

	while (cache.find('\n') == std::string::npos && (rc = recv(fd, buf, BUFSIZE, 0))) {
		if (rc == 0) {
			this->CloseConnect = 1;
		}
		std::string str_buf(buf);
		cache = cache + str_buf;
	}
	std::string res;

	line = cache.substr(0, cache.find("\n"));
	//if (line == "" || line == "\r")
		//return 0;
	cache = cache.substr(cache.find(('\n')) + 1);
	//std::cout << "|" << cache << "|" << std::endl << std::endl << std::endl;
	if (cache == "")
		rc = 0;
	return (rc == 0 ? 0 : 1);
}
