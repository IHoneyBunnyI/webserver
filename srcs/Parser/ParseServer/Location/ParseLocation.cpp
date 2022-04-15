#include "Parser.hpp"

void ParseLocation(std::ifstream &stream, ServerConfig &server, std::string line) {
	Location location;

	Parser::replace_all(line, "\t", " ");
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
			Root(location, line);
		} else if (line.find("alias") != std::string::npos) {
			Alias(location, line);
		} else if (line.find("method") != std::string::npos) {
			Method(location, line);
		} else if (line.find("cgi_path") != std::string::npos) {
			CgiPath(location, line);
		} else if (line.find("cgi_extensions") != std::string::npos) {
			CgiExtensions(location, line);
		} else if (line.find("upload_pass") != std::string::npos) {
			UploadPass(location, line);
		} else if (line.find("index") != std::string::npos) {
			Index(location, line);
		} else if (line == "}") {
			break;
		} else {
			throw Parser::UnknownDirective(line);
		}
	}
	server.locations.push_back(location);
}
