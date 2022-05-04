#include "Parser.hpp"

void Index(Location &location, std::string line) {
	Parser::replace_all(line, "\t", " ");
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive.size() < 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[0] != "index") {
		throw Parser::UnknownDirective(directive[0]);
	}
	if (location.indexExist) {
		throw Parser::DirectiveDuplicate(directive[0]);
	}
	location.indexes.erase(location.indexes.begin(), location.indexes.end());
	for (uint i = 1; i < directive.size(); i++) {
		location.indexes.push_back(directive[i]);
	}
	location.indexExist = 1;
}
