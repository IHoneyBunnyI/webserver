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
	// тут при парсинге тоже необходимо отключать клиента this->close_connect, если есть ошибки запроса
	//std::cout << GREEN << line << WHITE;
	if (line == "\r\n" || line == "\n") {
		return;
	} else if (!firstLineExist(this->Method, this->Path, this->Version)) {
		if (std::count(line.begin(), line.end(), ' ') == 2) {
			//std::cout << GREEN << line << WHITE;
			this->Method = line.substr(0, line.find(' '));
			//std::cout << this->Method << std::endl;
			line = line.substr(line.find(' ') + 1);
			this->Path = line.substr(0, line.find(' '));
			//std::cout << this->Path << std::endl;
			line = line.substr(line.find(' ') + 1);
			if (line.find('\r') != std::string::npos) {
				this->Version = line.substr(0, line.find('\r'));
			} else {
				this->Version = line.substr(0, line.find('\n'));
			//std::cout << this->Version << std::endl;
			}
		} else {
			Server::Log("ERROR request : \'" + line + "\'");
			this->close_connect = 1;
			//std::cout << RED "ERROR" WHITE << std::endl;
		}
	}
}
