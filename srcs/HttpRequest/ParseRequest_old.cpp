#include "HttpRequest.hpp"
#include "webserv.hpp"

void HttpRequest::ParseRequest(std::string line) {
	if (this->RequestLineExist == 0) {
		RequestLine(line);
		this->RequestLineExist = 1;
	} else if (this->HeadersExist == 0) {
		if (line == "" || line == "\r") {
			this->HeadersExist = 1;
		} else {
			AddHeader(line);
		}
	}
}
