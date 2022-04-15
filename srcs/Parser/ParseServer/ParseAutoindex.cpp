#include "Parser.hpp"

void ParseAutoindex(ServerConfig &server, std::string line) {
	Parser::replace_all(line, "\t", " "); // заменяю все табы на пробелы
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive[0] != "autoindex") {
		throw Parser::UnknownDirective(directive[0]);
	}
	if (directive.size() != 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (server.autoindexExist) {
		throw Parser::DirectiveDuplicate(directive[0]);
	}
	if (directive[1] == "on") {
		server.autoindex = 1;
	} else if (directive[1] == "off") {
		server.autoindex = 0;
	} else {
		throw Parser::UnknownDirective(directive[1]);
	}
	server.autoindexExist = 1;
}
