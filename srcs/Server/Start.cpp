#include <poll.h>
#include <unistd.h>
#include "Server.hpp"
#include "webserv.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "ServerConfig.hpp"

void erase_fds(std::vector<pollfd> &fds) {
	for (std::size_t i = 0; i < fds.size(); i++) {
		if (fds[i].fd == -1)
			fds.erase(fds.begin() + i);
	}
}

#include <sys/socket.h>
void ReadRequest(Client& client) {
	char buf[BUFSIZE + 1];
	std::memset(buf, 0, BUFSIZE + 1);
	int ret = recv(client.Fd(), buf, BUFSIZE, 0);
	if (ret == 0) { //соединение отключено на стороне клиента
		client.SetConnected(false);
		return ;
	}
	if (ret < 0) {
		client.SetConnected(false);
	}
	else if (ret > 0) {
		client.ParseRequest(buf);
	}
}

void pMap(std::map<std::string, std::string> &map) {
	for (std::map<std::string, std::string>::iterator it = map.begin(); it != map.end(); it++) {
		std::cout << it->first << ":" << it->second << std::endl;
	}
}

void Server::Start() {
	//Server::Log("Start Server");

	while (1) {
		for (uint servCounter = 0; servCounter < this->servers.size(); servCounter++) {
			ServerConfig &server = this->servers[servCounter];
			int ret = poll(server.FdSet.data(), server.FdSet.size(), 1);
			if (ret < 0) {
				std::cout << "ERROR" << std::endl;
				break;
			}
			//проходим по всем фд сервера для проверки
			//в случае елси где-то произошло событие это значит что клиент подключился и надо читать
			for (uint i = 0; i < server.ServerSockets.size(); i++) {
				if (server.ServerSockets[i]->revents & POLLIN) {
					OpenConnection(server, server.ServerSockets[i]);
				}
			}
			//std::cout << server.Clients.size() << std::endl;
			for (uint i = 0; i < server.Clients.size(); i++) {
				Client &client = server.Clients[i];
				if (client.Revents() & POLLIN) {
					ReadRequest(client);
					if (!client.Connected()) {
						client.Close();
						continue;
					}
					pMap(client.Headers);
				}
			}
			//очищаю вектор отключенных клиентов
			for (uint i = 0; i < server.Clients.size(); i++) {
				if (server.Clients[i].Fd() == -1) {
					server.Clients.erase(server.Clients.begin() + i);
				}
			}
		}
	}
	std::cout << "Сюда не должен был зайти" << std::endl;
}
