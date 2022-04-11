#include "HttpRequest.hpp"
#include "Server.hpp"
#include "webserv.hpp"
#include <sstream>
#include <sys/socket.h>
#define BUFSIZE 5

std::string HtppRequest::ReadRequest(int fd) {
	static std::string cache;
	char buf[BUFSIZE + 1];
	int rc;
	std::memset(buf, 0, BUFSIZE + 1);

	rc = 1;
		//std::cout << "AAA" << std::endl;
	while (cache.find('\n') == std::string::npos) {
		rc = recv(fd, buf, BUFSIZE, 0);
		if (rc < 0) {
			std::cout << "FULL READ" << std::endl;
			break; //full data read
		}
		if (rc == 0) {
			this->close_connect = 1;
			std::cout << "CLOSE CONNECT!" << std::endl;
			break;
		}
		std::string str_buf(buf);
		cache = cache + str_buf;
	}
	std::string res;
	if (rc > 0) {
		res = cache.substr(0, cache.find('\n') + 1);
		cache = cache.substr(cache.find('\n') + 1);
	} else {
		cache = "";
		res = "\r\n";
	}
	//std::cout << res;
	return res;
}
