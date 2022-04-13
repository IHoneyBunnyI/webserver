#include "Parser.hpp"
#include "Server.hpp"
#include <fstream>

static ServerConfig ParseServer(std::ifstream &stream) {
	ServerConfig server;

	std::string line;
	Parser::getLine(stream, line);
	if (line != "{")
		throw Parser::OpeningBracketExpected();

	return server;
}

unsigned int Parser::numLine = 1;

void Parser::ParseConfig()
{
	//std::ifstream file(this->configFile);
	std::ifstream stream(Parser::configFile);
	if (!stream) {
		throw FileNotOpen();
	}

	std::string line;
	//unsigned int numLine = 1;
	while (stream)
	{
		//std::string tmp;
		Parser::getLine(stream, line);
		if (line == "")
			continue;
		Parser::trim(line);
		if (line == "server") {
			try {
				ServerConfig serv = ParseServer(stream);
			} catch (std::exception &ex) {
				throw Parser::OpeningBracketExpected();
			}
			//this->servers.push_back(serv);
			//std::cout << Parser::numLine << " " + line << std::endl;
		}
	}
}
