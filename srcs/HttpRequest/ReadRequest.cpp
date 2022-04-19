#include "HttpRequest.hpp"
#include "Server.hpp"
#include "webserv.hpp"
#include <sstream>
#include <sys/socket.h>
#define BUFSIZE (1 << 20)

std::string HttpRequest::ReadRequest(int fd, int &ReadRequest) {
	static std::string cache;
	std::string line;
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
	cache = cache.substr(cache.find(('\n')) + 1);
	if ((line == "" && cache != "") || (line == "\r" && cache != "")) {
		std::cout << "cache != \"\"" << std::endl;
		std::cout << "cache:"<< cache << std::endl;
	}
	if ((line == "" && cache == "") || (line == "\r" && cache == "")) {
		std::cout << "CRLF!" << std::endl;
		std::cout << "cache:"<< cache << std::endl;
		ReadRequest = 1;
	}
	//if (line == "" && cache != "") {
	//} 
	return (line);
}

//int HttpRequest::ReadRequest(std::string &line, int fd) {
	//static std::string cache;
	//char buf[BUFSIZE + 1];
	//int rc = 1;
	//std::memset(buf, 0, BUFSIZE + 1);

	//while (cache.find('\n') == std::string::npos && (rc = recv(fd, buf, BUFSIZE, 0))) {
		//if (rc == 0) {
			//this->CloseConnect = 1;
		//}
		//std::string str_buf(buf);
		//cache = cache + str_buf;
	//}
	//std::string res;

	//line = cache.substr(0, cache.find("\n"));
	//cache = cache.substr(cache.find(('\n')) + 1);
	//return (1);
//}
