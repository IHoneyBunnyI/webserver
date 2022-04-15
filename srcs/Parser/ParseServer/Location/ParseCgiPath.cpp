#include "Parser.hpp"

void ParseCgiPath(Location &location, std::string line) {
	Parser::replace_all(line, "\t", " ");
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive.size() != 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[0] != "cgi_path") {
		throw Parser::UnknownDirective(directive[0]);
	}
	if (location.cgi_pathExist) {
		throw Parser::DirectiveDuplicate(directive[0]);
	}
	if (directive[1][directive[1].size() - 1] != '/') {
		directive[1] += '/';
	}
	location.cgi_path = directive[1];
	location.cgi_pathExist = 1;
}
