#include "Parser.hpp"

void ParseAlias(Location &location, std::string line) {
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive.size() != 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[0] != "alias") {
		throw Parser::UnknownDirective(directive[0]);
	} else if (location.rootExist) {
		throw Parser::AliasDuplicateRootExists();
	} else if (location.aliasExist) {
		throw Parser::AliasDuplicate();
	}
	if (directive[1][directive[1].size() - 1] != '/')
		directive[1] += '/';
	location.alias = directive[1];
	location.aliasExist = 1;
}
