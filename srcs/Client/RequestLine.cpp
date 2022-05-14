#include "Client.hpp"
#include "Parser.hpp"

static int AvailableMethod(std::string token) {
	if (token == "GET" || token == "POST" || token == "DELETE") {
		return 1;
	}
	return 0;
}

void Client::RequestLine(std::string line) {
	this->RequestLineExist = true;
	Parser::replace_all(line, "\t", " ");
	Parser::replace_all(line, "\r", " ");
	Parser::trim(line);
	std::vector<std::string> tokens = Parser::split(line, " ");
	if (tokens.size() != 3) {
		this->ResponseStatus = 400;
		return;
	}
	if (AvailableMethod(tokens[0]) && tokens[1][0] == '/' && tokens[2].find("HTTP/") != std::string::npos) {
		this->Method = tokens[0];
		this->Path = tokens[1];
	} else {
		this->ResponseStatus = 400;
		return;
	}
	if (tokens[2] == "HTTP/1.1") {
		this->Version = tokens[2];
	} else {
		this->ResponseStatus = 505;
		return;
	}
	std::cout << this->ResponseStatus << std::endl;
}
