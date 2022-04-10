#include "HttpRequest.hpp"
#include "Server.hpp"
#include "webserv.hpp"
#include <sstream>
#include <sys/socket.h>
#define BUFSIZE 5

void HtppRequest::ParseRequest(int &close_connect, int fd) {
	char buffer[BUFSIZE];
	memset(buffer, 0, BUFSIZE);
	close_connect = 0;
	std::istringstream input;
	std::string tmp;
	std::string line;
	while (1)
	{
		int rc = recv(fd, buffer, sizeof(buffer), 0);
		if (rc < 0)
			break; //full data read
		if (rc == 0)
		{
			close_connect = 1;
			break;
		}
		std::string read_line(buffer, BUFSIZE);
		if (tmp != "") {
			line = tmp + read_line;
		} else {
			line = read_line;
		}
		std::istringstream input(line);
		std::getline(input, line);
			//std::cout << line << std::endl;
		std::string pred_line;
		while (1) {
			if (line == "\r") {
				//конец запроса
				std::cout << RED "END REQUEST" WHITE << std::endl;
				break;
			}
			if (line == pred_line) { // в случае если getline не продолжает читать и изменять line
				//std::cout << RED "This line is readed!" WHITE << std::endl;
				//std::cout << YELLOW + line + WHITE << std::endl;
				tmp = line;
				break;
			}
			if (line.find('\r') != std::string::npos) {
				//отмечаем каждую строчку
				//std::cout << "find " << line << std::endl;
				//тут необходимо парсить строки
			} else {
				tmp = line;
				break;
			}
			pred_line = line;
			std::getline(input, line);
			//std::cout << "GELINE" << std::endl;
		}
		memset(buffer, 0, BUFSIZE);
			//if (this->Method == "") {
				//this->Method = line.substr(0, line.find(' '));
				//line = line.substr(line.find(' ') + 1);
				//this->Path = line.substr(0, line.find(' '));
				//line = line.substr(line.find(' ') + 1);
				//this->Version = line.substr(0, line.find(' '));
			//}
		//нужно попробовать getline
	}
}
