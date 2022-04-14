#include "Parser.hpp"

void ParseMaxBodySize(ServerConfig &server, std::string line) {
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive.size() != 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[0] != "client_max_body_size") {
		throw Parser::UnknownDirective(directive[0]);
	}
	server.client_max_body_size = std::stoi(directive[1]);
}
