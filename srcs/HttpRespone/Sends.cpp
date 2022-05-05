#include "HttpResponse.hpp"
#include "Server.hpp"
#include <sys/socket.h>
#include <fstream>
#define BUFSIZE (1 << 20)

void HttpResponse::SendHttp(std::string statusLine, std::string Headers, std::string path) {
	int ret = 1;
	std::string Http = statusLine + Headers;
	ret = send(this->fd, Http.c_str(), Http.length(), 0);
	if (ret <= 0) {
		Server::Log("send status line and headers failed");
		this->CloseConnect = 1;
	}
	
	char buf[BUFSIZE + 1];
	std::memset(buf, 0, BUFSIZE);
	std::ifstream stream(path);
	while (stream)
	{
		stream.read(buf, BUFSIZE);
		ret = send(this->fd, buf, BUFSIZE, 0);
		if (ret <= 0) {
			std::cout << "send error page failed" << std::endl;
			this->CloseConnect = 1;
			break;
		}
	}
	stream.close();
}

void HttpResponse::SendDefaultErrorPage(std::string statusLine, std::string Headers, std::string error_page) {
	int ret = 1;
	std::string Http = statusLine + Headers + error_page;
	ret = send(this->fd, Http.c_str(), Http.length(), 0);
	if (ret <= 0) {
		Server::Log("send default error page failed");
		this->CloseConnect = 1;
	}
}

//void HttpResponse::SendPage(std::string path) {

	//std::ifstream stream(path);
	//while (stream)
	//{
		//int ret = 1;
		//std::string line;
		//std::getline(stream, line);
		//if (line.empty())
			//return;
		//line += "\n";
		//ret = send(this->fd, line.c_str(), line.length(), 0);
		//if (ret <= 0) {
			//std::cout << "send error page failed" << std::endl;
			//this->CloseConnect = 1;
			//stream.close();
			//break;
		//}
	//}
	//stream.close();
//}
