#include "Parser.hpp"
#include "Server.hpp"
#include <fstream>

unsigned int Parser::numLine = 1;

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
		ServerConfig serv;
		if (line == "" || (line.find("/*") != std::string::npos && line.find("*/") != std::string::npos))
			continue;
		if (line == "server") {
			serv = ParseServer(stream);
			this->servers.push_back(serv);
		} else {
			throw UnknownDirective(line);
		}
	}
}
