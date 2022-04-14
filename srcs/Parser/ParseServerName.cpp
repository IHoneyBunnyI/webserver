#include "Parser.hpp"

void ParseServerName(ServerConfig &server, std::string line) {
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive[0] != "server_name") {
		throw Parser::UnknownDirective(directive[0]);
	}
	for (unsigned int i = 1; i < directive.size(); i++) {
		server.server_names.push_back(directive[i]);
	}
}
