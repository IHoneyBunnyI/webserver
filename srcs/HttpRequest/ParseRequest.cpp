#include "HttpRequest.hpp"
#include "Server.hpp"
#include "webserv.hpp"
#include <sys/socket.h>

void HtppRequest::ParseRequest(std::string line) {
	(void)line;
	if (this->Method == "" &&
		this->Path == "" &&
		this->Version == "") {
		//std::cout << YELLOW << line << WHITE << std::endl;
		this->Method = line.substr(0, line.find(' '));
		line = line.substr(line.find(' ') + 1);
		this->Path = line.substr(0, line.find(' '));
		line = line.substr(line.find(' ') + 1);
		this->Version = line.substr(0, line.find('\r'));
		//НЕОБХОДИМО ДОБАВИТЬ ОБРАБОТКУ ОШИБОК
	}
}
