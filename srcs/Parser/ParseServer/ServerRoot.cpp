#include "Parser.hpp"

void ServerRoot(ServerConfig &server, std::string line) {
	Parser::replace_all(line, "\t", " "); // заменяю все табы на пробелы
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive.size() != 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[0] != "root") {
		throw Parser::UnknownDirective(directive[0]);
	} else if (server.rootExist) {
		throw Parser::DirectiveDuplicate(directive[0]);
	}
	if (directive[1][directive[1].size() - 1] != '/')
		directive[1] += '/';
	server.root = directive[1];
	server.rootExist = 1;
}
