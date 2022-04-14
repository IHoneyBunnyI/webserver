#include "Parser.hpp"

void ParseRoot(Location &location, std::string line) {
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive.size() != 2) {
		throw Parser::ToManyArgumentsInDirective();
	}
	if (directive[0] != "root") {
		throw Parser::UnknownDirective(directive[0]);
	} else if (location.hasRoot) {
		throw Parser::RootDuplicate();
	} else if (location.hasAlias) {
		throw Parser::RootDuplicateAliasExists();
	}
}
