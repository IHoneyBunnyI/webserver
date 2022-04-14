#include "Parser.hpp"

void ParseListen(ServerConfig &server, std::string line) {
	if (server.defaultListen) {
		server.ips.erase(server.ips.begin());
		server.ports.erase(server.ports.begin());
		server.defaultListen = 0;
	}
	//парсим директиву, если имеются проблемы выкидываем исключения
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive.size() != 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[0] != "listen") {
		throw Parser::UnknownDirective(directive[0]);
	}
	std::vector<std::string> ipPort = Parser::split(directive[1], ":");
	std::string ip;
	std::string port;

	if (ipPort.size() == 2) {
		ip = ipPort[0];
		port = ipPort[1];
	} else if (ipPort.size() == 1 && ipPort[0].find(".") != std::string::npos) {
		ip = ipPort[0];
		port = "80";
	} else {
		ip = "0.0.0.0";
		port = ipPort[0];
	}
	server.ips.push_back(ip);
	server.ports.push_back(std::stoi(port));
}
