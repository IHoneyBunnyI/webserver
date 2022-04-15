#include "Parser.hpp"

void ParseRoot(Location &location, std::string line) {
	Parser::replace_all(line, "\t", " "); // заменяю все табы на пробелы
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive.size() != 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[0] != "root") {
		throw Parser::UnknownDirective(directive[0]);
	} else if (location.rootExist) {
		throw Parser::DirectiveDuplicate(directive[0]);
	} else if (location.aliasExist) {
		throw Parser::RootDuplicateAliasExists();
	}
	if (directive[1][directive[1].size() - 1] != '/')
		directive[1] += '/';
	location.root = directive[1];
	location.rootExist = 1;
}
