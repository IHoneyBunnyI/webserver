#include "Parser.hpp"

void ParseListen(ServerConfig &server, std::string line) {
	//парсим директиву, если имеются проблемы выкидываем исключения
	Parser::replace_all(line, "\t", " "); // заменяю все табы на пробелы
	std::vector<std::string> directive = Parser::split(line, " ");
	if (directive.size() != 2) {
		throw Parser::InvalidNumberOfArgument();
	}
	if (directive[0] != "listen") {
		throw Parser::UnknownDirective(directive[0]);
	}
	std::vector<std::string> ipPort = Parser::split(directive[1], ":");
	std::string ip;
	int port;

	if (ipPort.size() == 2) {
		ip = ipPort[0];
		port = std::stoi(ipPort[1]);
	} else if (ipPort.size() == 1 && ipPort[0].find(".") != std::string::npos) {
		ip = ipPort[0];
		port = std::stoi("80");
	} else {
		ip = "0.0.0.0";
		port = std::stoi(ipPort[0]);
	}
	if (server.listenExist == 0) {
		server.ips.erase(server.ips.begin());
		server.ports.erase(server.ports.begin());
		server.listenExist = 1;
	}
	server.ips.push_back(ip);
	server.ports.push_back(port);
}
