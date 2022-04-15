#include "Parser.hpp"

void Method(Location &location, std::string line) {
	Parser::replace_all(line, "\t", " "); // заменяю все табы на пробелы
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive.size() < 2 || directive.size() > 4) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[0] != "method") {
		throw Parser::UnknownDirective(directive[0]);
	}
	if (location.methodsExist) {
		throw Parser::DirectiveDuplicate(directive[0]);
	}
	for (unsigned int i = 1; i < directive.size(); i++) {
		if (directive[i] == "GET" || directive[i] == "POST" || directive[i] == "DELETE") {
			continue;
		} else {
			throw Parser::UnknownDirective(directive[i]);
		}
	}
	location.methods.erase(location.methods.begin(), location.methods.end());
	for (unsigned int i = 1; i < directive.size(); i++) {
		//std::cout << "A: " << directive[i];
		location.methods.push_back(directive[i]);
	}
	std::cout << location.methods[0];
	location.methodsExist = 1;
}
