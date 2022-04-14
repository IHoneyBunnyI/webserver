#include "Parser.hpp"
#include "Server.hpp"
#include <fstream>

static ServerConfig ParseServer(std::ifstream &stream) {
	ServerConfig server;

	std::string line;
	Parser::getLine(stream, line);
	if (line != "{")
		throw Parser::OpeningBracketExpected();
	while (line != "}") {
		Parser::getLine(stream, line);
		Parser::trim(line);
		if (line == "" || (line.find("/*") != std::string::npos && line.find("*/") != std::string::npos))
			continue;
		if (line.find("listen") != std::string::npos) {
			ParseListen(server, line);
		} else if (line.find("server_name") != std::string::npos) {
			ParseServerName(server, line);
		} else if (line.find("client_max_body_size") != std::string::npos) {
			ParseMaxBodySize(server, line);
		} else if (line.find("error_page") != std::string::npos) {
			ParseErrorPage(server, line);
		} else if (line.find("autoindex") != std::string::npos) {
			ParseAutoindex(server, line);
		} else if (line.find("location") != std::string::npos) {
			ParseLocation(stream, server, line);
		}

	}
	std::cout << server;
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
	while (stream) {
		//std::string tmp;
		Parser::getLine(stream, line);
		Parser::trim(line);
		if (line == "" || (line.find("/*") != std::string::npos && line.find("*/") != std::string::npos))
			continue;
		if (line == "server") {
			try {
				ServerConfig serv = ParseServer(stream);
			} catch (Parser::OpeningBracketExpected &e) {
				throw e;
			} catch (Parser::ToManyArgumentsInDirective &e) {
				throw e;
			} catch (Parser::UnknownDirective &e) {
				throw e;
			} catch (Parser::RootDuplicate &e) {
				throw e;
			} catch (Parser::AliasDuplicate &e) {
				throw e;
			} catch (Parser::RootDuplicateAliasExists &e) {
				throw e;
			} catch (Parser::AliasDuplicateRootExists &e) {
				throw e;
			}
			//this->servers.push_back(serv);
			//std::cout << Parser::numLine << " " + line << std::endl;
		} else {
			throw UnknownDirective(line); //тестовое исключение в этом месте
		}
	}
}
