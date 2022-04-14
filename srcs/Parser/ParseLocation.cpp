#include "Parser.hpp"

void ParseLocation(std::ifstream &stream, ServerConfig &server, std::string line) {
	(void)stream;
	(void)server;
	(void)line;
	Location location;

	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive[0] != "location") {
		throw Parser::UnknownDirective(directive[0]);
	}
	if (directive.size() != 2) {
		throw Parser::ToManyArgumentsInDirective();
	}
	if (directive[1][directive[1].size() - 1] != '/') //проверяю последний символ в location, если не '/', добавляю
		directive[1] += '/';
	location.location = directive[1];

	//начало парсинга location
	
	server.locations.push_back(location);
}
