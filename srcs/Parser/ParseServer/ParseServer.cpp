#include "Parser.hpp"

ServerConfig ParseServer(std::ifstream &stream) {
	ServerConfig server;

	std::string line;
	Parser::getLine(stream, line);
	if (line != "{")
		throw Parser::OpeningBracketExpected();
	while (line != "}") {
		Parser::getLine(stream, line);
		Parser::trim(line);
		if (line == "" || (line.find("/*") != std::string::npos && line.find("*/") != std::string::npos))
			continue;
		if (line.find("listen") != std::string::npos) {
			Listen(server, line);
		} else if (line.find("server_name") != std::string::npos) {
			ServerName(server, line);
		} else if (line.find("client_max_body_size") != std::string::npos) {
			MaxBodySize(server, line);
		} else if (line.find("error_page") != std::string::npos) {
			ErrorPage(server, line);
		} else if (line.find("autoindex") != std::string::npos) {
			Autoindex(server, line);
		} else if (line.find("root") != std::string::npos) {
			ServerRoot(server, line);
		} else if (line.find("location") != std::string::npos) {
			ParseLocation(stream, server, line);
		} else if (line == "}") {
			break;
		} else {
			throw Parser::UnknownDirective(line);
		}

	}
	//std::cout << server;
	return server;
}

