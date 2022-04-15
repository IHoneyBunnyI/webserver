#include "Parser.hpp"

void ParseMaxBodySize(ServerConfig &server, std::string line) {
	Parser::replace_all(line, "\t", " "); // заменяю все табы на пробелы
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive.size() != 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[0] != "client_max_body_size") {
		throw Parser::UnknownDirective(directive[0]);
	}
	if (server.client_max_body_sizeExist) {
		throw Parser::DirectiveDuplicate(directive[0]);
	}
	server.client_max_body_size = std::stoi(directive[1]);
	server.client_max_body_sizeExist = 1;
}
