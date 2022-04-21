#include "HttpResponse.hpp"
#include "Server.hpp"
#include <sys/socket.h>
#include <fstream>

void HttpResponse::SendStatusLine(std::string statusLine) {
	if ((send(fd, statusLine.c_str(), statusLine.length(), 0)) <= 0) {
		Server::Log("send status line failed");
		this->CloseConnect = 1;
	}
}
void HttpResponse::SendHeaders(std::string Headers) {
	if ((send(fd, Headers.c_str(), Headers.length(), 0)) <= 0) {
		Server::Log("send headers failed");
		this->CloseConnect = 1;
	}
}
void HttpResponse::SendDefaultErrorPage(std::string error_page) {
	if ((send(fd, error_page.c_str(), error_page.length(), 0)) <= 0) {
		Server::Log("send default error page failed");
		this->CloseConnect = 1;
	}
}

void HttpResponse::SendPage(int fd, std::string path) {

	std::ifstream stream(path);
	while (stream)
	{
		std::string line;
		std::getline(stream, line);
		if (line.empty())
			return;
		line += "\n";
		if ((send(fd, line.c_str(), line.length(), 0)) <= 0) {
			std::cout << "send error page failed" << std::endl;
			this->CloseConnect = 1;
		}
	}
}
