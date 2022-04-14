#include "Parser.hpp"

void ParseMethod(Location &location, std::string line) {
	location.methods.erase(location.methods.begin(), location.methods.end());
	std::vector<std::string> directive = Parser::split(line, " ");
	if (location.methodsExist) {
		throw Parser::MethodDuplicate();
	}
	if (directive.size() < 2 || directive.size() > 4) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[0] != "method") {
		throw Parser::UnknownDirective(directive[0]);
	}
	for (unsigned int i = 1; i < directive.size(); i++) {
		location.methods.push_back(directive[i]);
	}
	location.methodsExist = 1;
}
