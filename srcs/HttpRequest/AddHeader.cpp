#include "HttpRequest.hpp"
#include "webserv.hpp"
#include "Parser.hpp"

void HttpRequest::AddHeader(std::string line) {
	Parser::replace_all(line, "\t", " ");
	Parser::replace_all(line, "\r", " ");
	Parser::trim(line);
	std::vector<std::string> tokens;
	int dots = line.find(":");
	tokens.push_back(line.substr(0, dots));
	tokens.push_back(line.substr(dots + 1));
	if (tokens[0].find(' ') != std::string::npos) {
		this->ResponseStatus = 400;
		this->State = ALL;
		return;
	}
	Parser::trim(tokens[1]);
	if (Headers.find(tokens[0]) == Headers.end()) {
		Headers[tokens[0]] = tokens[1];
	}
}
