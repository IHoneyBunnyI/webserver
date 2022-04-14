#include "Parser.hpp"

void ParseCgiExtensions(Location &location, std::string line) {
	//if (location.cgiExtensionsExist) {
		//throw Parser::MethodDuplicate();
	//}
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive.size() < 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[0] != "cgi_extensions") {
		throw Parser::UnknownDirective(directive[0]);
	}
	for (unsigned int i = 1; i < directive.size(); i++) {
		location.cgi_extensions.push_back(directive[i]);
	}
	//location.cgiExtensionsExtst = 1;
}
