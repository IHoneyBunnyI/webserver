#include "Parser.hpp"

void ParseUploadPass(Location &location, std::string line) {
	//if (location.uploadPassExist) {
		//throw Parser::DirectiveExist("upload_pass");
	//}
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive.size() != 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[0] != "upload_pass") {
		throw Parser::UnknownDirective(directive[0]);
	}
	if (directive[1][directive[1].size() - 1] != '/') {
		directive[1] += '/';
	}
	location.upload_pass = directive[1];
	//location.uploadPassExist = 1;
}
