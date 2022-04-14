#include "Parser.hpp"

void ParseLocation(std::ifstream &stream, ServerConfig &server, std::string line) {
	Location location;

	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive[0] != "location") {
		throw Parser::UnknownDirective(directive[0]);
	}
	if (directive.size() != 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[1][directive[1].size() - 1] != '/') //проверяю последний символ в location, если не '/', добавляю
		directive[1] += '/';
	location.location = directive[1];

	//начало парсинга location
	Parser::getLine(stream, line);
	Parser::trim(line);
	if (line != "{") {
		throw Parser::OpeningBracketExpected();
	}
	while (line != "}") {
		Parser::getLine(stream, line);
		Parser::trim(line);
		if (line == "" || (line.find("/*") != std::string::npos && line.find("*/") != std::string::npos))
			continue;
		if (line.find("root") != std::string::npos) {
			ParseRoot(location, line);
		} else if (line.find("alias") != std::string::npos) {
			ParseAlias(location, line);
		} else if (line.find("method") != std::string::npos) {
			ParseMethod(location, line);
		} else if (line.find("cgi_path") != std::string::npos) {
			ParseCgiPath(location, line);
		} else if (line.find("cgi_extensions") != std::string::npos) {
			ParseCgiExtensions(location, line);
		} else if (line.find("upload_pass") != std::string::npos) {
			ParseUploadPass(location, line);
		}




	}
	server.locations.push_back(location);
}
