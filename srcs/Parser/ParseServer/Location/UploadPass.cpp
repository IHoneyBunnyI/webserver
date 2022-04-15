#include "Parser.hpp"

void UploadPass(Location &location, std::string line) {
	Parser::replace_all(line, "\t", " "); // заменяю все табы на пробелы
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive.size() != 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[0] != "upload_pass") {
		throw Parser::UnknownDirective(directive[0]);
	}
	if (location.upload_passExist) {
		throw Parser::DirectiveDuplicate(directive[0]);
	}
	if (directive[1][directive[1].size() - 1] != '/') {
		directive[1] += '/';
	}
	location.upload_pass = directive[1];
	location.upload_passExist = 1;
}
