#include "Parser.hpp"

void Alias(Location &location, std::string line) {
	Parser::replace_all(line, "\t", " ");
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive.size() != 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[0] != "alias") {
		throw Parser::UnknownDirective(directive[0]);
	} else if (location.rootExist) {
		throw Parser::AliasDuplicateRootExists();
	} else if (location.aliasExist) {
		throw Parser::DirectiveDuplicate(directive[0]);
	}
	if (directive[1][directive[1].size() - 1] != '/')
		directive[1] += '/';
	location.alias = directive[1];
	location.aliasExist = 1;
}
