#include "HttpRequest.hpp"
#include "webserv.hpp"

void HttpRequest::Body(std::string line) {
	if (line == "" || line == "\r") {
			return ;
	}
	std::cout << "GET BODY!" << std::endl;
}
