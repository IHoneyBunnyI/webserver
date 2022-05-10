#include "Parser.hpp"
#include "Server.hpp"
#include <fstream>

uint Parser::numLine = 1;

void Parser::ParseConfig()
{
	std::ifstream stream(Parser::configFile);
	if (!stream) {
		throw FileNotOpen();
	}

	std::string line;
	while (stream) {
		Parser::getLine(stream, line);
		Parser::trim(line);
		if (line == "" || (line.find("/*") != std::string::npos && line.find("*/") != std::string::npos))
			continue;
		if (line == "server") {
			ServerConfig serv = ParseServer(stream);
			this->servers.push_back(serv);
		} else {
			throw UnknownDirective(line);
		}
	}
}
