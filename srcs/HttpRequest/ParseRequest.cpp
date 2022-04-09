#include "HttpRequest.hpp"
#include "Server.hpp"
#include "webserv.hpp"
#include <sys/socket.h>

void HtppRequest::ParseRequest(int &close_connect, int fd) {
	char buffer[10000];
	memset(buffer, 0, 10000);
	close_connect = 0;
	std::string end;
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
		//std::string line;
		//std::string RequestPart = buffer;
		//while (line.find('\n') != std::string::npos) {
			//std::cout << "AAA" << std::endl;
			//memset(buffer, 0, 10000);
			//if (RequestPart.find('\n') != std::string::npos) {
				//line = RequestPart.substr(0, RequestPart.find('\n'));
			//}
			//else {
				//end = RequestPart;
			//}
			//if (this->Method == "") {
				//this->Method = line.substr(0, line.find(' '));
				//line = line.substr(line.find(' ') + 1);
				//this->Path = line.substr(0, line.find(' '));
				//line = line.substr(line.find(' ') + 1);
				//this->Version = line.substr(0, line.find(' '));
			//}
		//}
		//Server::Log(this->Method + " request with Path " + this->Path + "from " + std::to_string(fd) + " fd");
		//std::cout << this->Method << std::endl << this->Path << std::endl << this->Version << std::endl;
		//нужно попробовать getline
	}
}
