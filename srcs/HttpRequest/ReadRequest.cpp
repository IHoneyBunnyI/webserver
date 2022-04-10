#include "HttpRequest.hpp"
#include "Server.hpp"
#include "webserv.hpp"
#include <sstream>
#include <sys/socket.h>
#define BUFSIZE 2

void HtppRequest::ReadRequest(int &close_connect, int fd) {

	char buffer[BUFSIZE];
	memset(buffer, 0, BUFSIZE);
	close_connect = 0;
	std::istringstream input;
	std::string cache;
	std::string line;
	//std::string pred_line;
	//std::cout << "CAAAAAAAAALL" << std::endl;
	int crlf = 0;
	//int i = 0;
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
		std::string buff_str(buffer, sizeof(buffer));
		//std::cout << cache + buff_str << std::endl;
		std::string input_str(cache + buff_str);
		cache = "";
		if (input_str.find('\n') == std::string::npos) {
			cache = input_str;
			continue;
		}
		//std::cout << i << " " << ((input_str.find('\n') == std::string::npos) ? "NO\n" : "YES\n");
		//i++;
		//std::cout << input_str << std::endl;
		std::istringstream input(input_str);

		while (!crlf) {
			std::getline(input, line);
			//std::cout << YELLOW + line + WHITE << std::endl;
			if (line == "\r") {
				crlf = 1;
				std::cout << RED "END REQUEST" WHITE << std::endl;
				break;
			}
			if (line.find('\r') != std::string::npos) {
				std::cout << YELLOW + line + WHITE << std::endl;
			} else {
				cache = line;
				break;
			}
		}
		//считываю строку из стрима
		//getline(input, line);
	}
}
