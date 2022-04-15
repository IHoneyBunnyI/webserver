#include "Parser.hpp"
#include "ServerConfig.hpp"

void ParseErrorPage(ServerConfig &server, std::string line) {
	ErrorPage errPage;

	Parser::replace_all(line, "\t", " "); // заменяю все табы на пробелы
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive[0] != "error_page") {
		throw Parser::UnknownDirective(directive[0]);
	}
	// надо дабавить directive.size() <= 1
	for (unsigned int i = 1; i < directive.size() - 1; i++) {
		errPage.errors.push_back(std::stoi(directive[i]));
	}
	errPage.error_page = directive[directive.size() - 1];
	server.error_pages.push_back(errPage);
}
