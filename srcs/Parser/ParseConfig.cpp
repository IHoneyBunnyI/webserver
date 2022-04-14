#include "Parser.hpp"
#include "Server.hpp"
#include <fstream>

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
			} catch (Parser::InvalidNumberOfArgument &e) {
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
			} catch (Parser::MethodDuplicate &e) {
				throw e;
			}

			//this->servers.push_back(serv);
			//std::cout << Parser::numLine << " " + line << std::endl;
		} else {
			throw UnknownDirective(line); //тестовое исключение в этом месте
		}
	}
}
