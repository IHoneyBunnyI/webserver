#include "Parser.hpp"

void ParseServerName(ServerConfig &server, std::string line) {
	Parser::replace_all(line, "\t", " "); // заменяю все табы на пробелы
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive[0] != "server_name") {
		throw Parser::UnknownDirective(directive[0]);
	}
	if (directive.size() < 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	for (unsigned int i = 1; i < directive.size(); i++) {
		server.server_names.push_back(directive[i]);
	}
}
