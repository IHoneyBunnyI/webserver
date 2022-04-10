#include "HttpRequest.hpp"
#include "Server.hpp"
#include "webserv.hpp"
#include <sstream>
#include <sys/socket.h>
#define BUFSIZE 1 << 10

void HtppRequest::ReadRequest(int &close_connect, int fd) {

	char buffer[BUFSIZE];
	memset(buffer, 0, BUFSIZE);
	close_connect = 0;
	std::istringstream input;
	std::string tmp;
	std::string line;
	std::string pred_line;
	int i = 0;
	while (1) {
		line.clear();
		memset(buffer, 0, BUFSIZE);
		int rc = recv(fd, buffer, BUFSIZE, 0);
		if (rc < 0)
			break; //full data read
		if (rc == 0) {
			close_connect = 1;
			break;
		}

		//создаю стрим, что читать из него getline'ом
		std::string input_str(buffer, sizeof(buffer));
		std::istringstream input(tmp + input_str);

		//считываю строку из стрима
		getline(input, line);
		if (line == "\r") {
			std::cout << RED "REQUEST END" WHITE << std::endl;
			break;
		}
		if (line == pred_line) {
			break;
		}
		if (line.find('\r') != std::string::npos) {
			std::cout << i++ << " " << line << std::endl;
		}
		pred_line = line;
	}
}
