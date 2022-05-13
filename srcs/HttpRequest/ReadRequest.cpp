#include "HttpRequest.hpp"
#include "Server.hpp"
#include "webserv.hpp"
#include <sstream>
#include <sys/socket.h>

std::string HttpRequest::ReadRequest(int fd) {
static std::string cache;
	std::string line;
	char buf[BUFSIZE + 1];
	int rc = 1;
	std::memset(buf, 0, BUFSIZE + 1);

	while (cache.find('\n') == std::string::npos && (rc = recv(fd, buf, BUFSIZE, 0))) {
		//if (rc < 0) {
			//this->CloseConnect = 1;
			//std::cout << "CloseConnect" << rc << std::endl;
		//}
		std::string str_buf(buf);
		cache = cache + str_buf;
	}
	//std::cout << line << " " << cache << std::endl;
	//this->first нужен для того чтобы пропускать пустые запросы в самом начале, да костыль, но рабоатет
	if (this->First == 0 && cache == "\n") { // костыль для обработки всех пустых запросов до строки запроса
		cache = "";
		return "";
	}
	this->First = 1;
	line = cache.substr(0, cache.find("\n"));
	cache = cache.substr(cache.find(('\n')) + 1);
	//std::cout << line << std::endl;

	//std::cout << "Before Parsing " << this->ResponseStatus << std::endl;
	this->ParseRequest_old(line);
	//std::cout << "After Parsing " << this->ResponseStatus << std::endl;

	if (this->HeadersExist && (this->Headers.count("Content-Length") == 1 || (line == "" && cache != "") || (line == "\r" && cache != ""))) {
		this->State = NEED_BODY;
	} else if ((line == "" && cache == "") || (line == "\r" && cache == "")) {
		this->State = ALL;
	}
	return (line);
}
