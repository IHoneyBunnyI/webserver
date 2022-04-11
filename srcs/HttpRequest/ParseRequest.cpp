#include "HttpRequest.hpp"
#include "Server.hpp"
#include "webserv.hpp"
#include <sys/socket.h>

int firstLineExist(std::string &m, std::string &p, std::string &v) {
	if (m == "" && p == "" && v == "") {
		return 0;
	}
	return 1;
}

void HtppRequest::ParseRequest(std::string line) {
	(void)line;
	// тут при парсинге тоже необходимо отключать клиента this->close_connect, если есть ошибки запроса
	if (!firstLineExist(this->Method, this->Path, this->Version)) {
		//std::cout << YELLOW << line << WHITE << std::endl;
		//std::cout <<std::count(line.begin(), line.end(), ' ') << std::endl;
		if (std::count(line.begin(), line.end(), ' ') == 2) {
			this->Method = line.substr(0, line.find(' '));
			line = line.substr(line.find(' ') + 1);
			this->Path = line.substr(0, line.find(' '));
			line = line.substr(line.find(' ') + 1);
			this->Version = line.substr(0, line.size() - 1);
		} else {
			Server::Log("ERROR request : \'" + line + "\'");
			this->close_connect = 1;
			//std::cout << RED "ERROR" WHITE << std::endl;
		}
		//НЕОБХОДИМО ДОБАВИТЬ ОБРАБОТКУ ОШИБОК
	}
}
