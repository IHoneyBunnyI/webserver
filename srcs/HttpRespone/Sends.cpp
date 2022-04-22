#include "HttpResponse.hpp"
#include "Server.hpp"
#include <sys/socket.h>
#include <fstream>

void HttpResponse::SendStatusLine(std::string statusLine) {
	if ((send(this->fd, statusLine.c_str(), statusLine.length(), 0)) <= 0) {
		Server::Log("send status line failed");
		this->CloseConnect = 1;
	}
}
void HttpResponse::SendHeaders(std::string Headers) {
	if ((send(this->fd, Headers.c_str(), Headers.length(), 0)) <= 0) {
		Server::Log("send headers failed");
		this->CloseConnect = 1;
	}
}
void HttpResponse::SendDefaultErrorPage(std::string error_page) {
	if ((send(this->fd, error_page.c_str(), error_page.length(), 0)) <= 0) {
		Server::Log("send default error page failed");
		this->CloseConnect = 1;
	}
}

void HttpResponse::SendPage(std::string path) {

	std::ifstream stream(path);
	while (stream)
	{
		std::string line;
		std::getline(stream, line);
		//std::cout << "\\"<< line << std::endl;
		if (line.empty())
			return;
		line += "\n";
		if ((send(this->fd, line.c_str(), line.length(), 0)) <= 0) {
			std::cout << "send error page failed" << std::endl;
			this->CloseConnect = 1;
		}
	}
	stream.close();
}
