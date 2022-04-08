#include "HttpRequest.hpp"
#include "webserv.hpp"
#include <sys/socket.h>

void HtppRequest::ParseRequest(int &close_connect, int fd) {
	char buffer[10000];
	memset(buffer, 0, 10000);
	close_connect = 0;
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
		std::string RequestPart = buffer;
		std::string line;
		memset(buffer, 0, 1000);
		if (RequestPart.find('\n') != std::string::npos) {
			line = RequestPart.substr(0, RequestPart.find('\n'));
		}
		else {
			std::cout << RED << "DDDDDDDDDD";
		}
		if (this->Method == "") {
			this->Method = line.substr(0, line.find(' '));
			line = line.substr(line.find(' ') + 1);
			this->Path = line.substr(0, line.find(' '));
			line = line.substr(line.find(' ') + 1);
			this->Version = line.substr(0, line.find(' '));
		}
		//std::cout << this->Method << std::endl << this->Path << std::endl << this->Version << std::endl;
	}
}
