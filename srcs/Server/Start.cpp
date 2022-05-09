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
		for (std::vector<ServerConfig>::iterator server = servers.begin(); server != servers.end(); server++) {
			int ret = poll(server->FdSet.data(), server->FdSet.size(), 1000);
			//std::cout << server->FdSet.size() << std::endl;
			if (ret < 0) {
				std::cout << "ERROR" << std::endl;
				break;
			}
			for (uint i = 0; i < server->ServerSockets.size(); i++) {
				//std::cout << "A" << std::endl;
				std::cout << server->ServerSockets[i]->revents << std::endl;
				std::cout << POLLIN << std::endl;
				if (server->ServerSockets[i]->revents & POLLIN) {
					std::cout << "OPEN NEW CLIENT" << std::endl;
					server->ServerSockets[i]->revents &= ~POLLIN;
					//acceptClient(server->ServerSockets[i]);
				}
			}
			//std::cout << "AAAAAAAAAAAAA" << std::endl;
		}
	}
	std::cout << "Сюда не должен был зайти" << std::endl;
}
