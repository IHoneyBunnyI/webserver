#include "HttpRequest.hpp"
#include "Server.hpp"
#include "webserv.hpp"
#include <sstream>
#include <sys/socket.h>
#define BUFSIZE 100

void HtppRequest::ParseRequest(int &close_connect, int fd) {
	char buffer[BUFSIZE];
	memset(buffer, 0, BUFSIZE);
	close_connect = 0;
	std::istringstream input;
	std::string tmp;
	std::string line;
	std::string pred_line;
	while (1)
	{
		line.clear();
		int rc = recv(fd, buffer, sizeof(buffer), 0);
		if (rc < 0)
			break; //full data read
		if (rc == 0)
		{
			close_connect = 1;
			break;
		}

		//создаю стрим, что читать из него getline'ом
		std::string input_str(buffer, sizeof(buffer));
		std::istringstream input(input_str);
	}
}
