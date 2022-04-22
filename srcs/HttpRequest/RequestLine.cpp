#include "HttpRequest.hpp"
#include "Parser.hpp"
#include "webserv.hpp"

static int AvailableMethod(std::string token) {
	if (token == "GET" || token == "POST" || token == "DELETE") {
		return 1;
	}
	return 0;
}

void HttpRequest::RequestLine(std::string line) {
	Parser::replace_all(line, "\t", " ");
	Parser::replace_all(line, "\r", " ");
	Parser::trim(line);
	std::vector<std::string> tokens = Parser::split(line, " ");
	//std::cout << "  |" + line << std::endl;
	if (tokens.size() != 3) {
		this->ResponseStatus = 400;
		this->State = ALL;
		return;
	}
	//std::cout << "After Parsing " << this->ResponseStatus << std::endl;
	if (AvailableMethod(tokens[0])) {
		this->Method = tokens[0];
	} else {
		this->ResponseStatus = 400;
		this->State = ALL;
		return;
	}
	if (tokens[1][0] == '/') {
		this->Path = tokens[1];
	} else {
		this->ResponseStatus = 400;
		this->State = ALL;
		return;
	}
	if (tokens[2] == "HTTP/1.1") {
		this->Version = tokens[2];
	} else {
		this->ResponseStatus = 400;
		this->State = ALL;
		return;
	}
}
