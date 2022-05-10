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

void Server::Start() {
	//когда буду переписывать ядро
	//
	//Для начала необходимо пройти по всем сокетам, которые были спрашены с конфиг файла, проверить у них события,
	//в случае, если произошло событие, нужно сделать accept и доавить этот сокет к фдшникам, это будет клиентский сокет
	//далее необходимо пройти по всем клиентским сокетам и посмотреть на их события, если где-то появилось, значит там надо читать
	//std::cout << servers[0] << std::endl;
	Server::Log("Start Server");

	while (1) {
		for (uint servCounter = 0; servCounter < this->servers.size(); servCounter++) {
			ServerConfig &server = this->servers[servCounter];
			int ret = poll(server.FdSet.data(), server.FdSet.size(), 1);
			if (ret < 0) {
				std::cout << "ERROR" << std::endl;
				break;
			}
			for (uint i = 0; i < server.ServerSockets.size(); i++) {
				if (server.ServerSockets[i]->revents & POLLIN) {
					OpenConnection(server, server.ServerSockets[i]);
				}
			}
		}
	}
	std::cout << "Сюда не должен был зайти" << std::endl;
}
