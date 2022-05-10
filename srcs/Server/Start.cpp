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
			//проходим по всем фд сервера для проверки
			//в случае елси где-то произошло событие это значит что клиент подключился и надо читать
			for (uint i = 0; i < server.ServerSockets.size(); i++) {
				if (server.ServerSockets[i]->revents & POLLIN) {
					std::cout << "NEW" << std::endl;
					OpenConnection(server, server.ServerSockets[i]);
				}
			}
			for (uint i = 0; i < server.ClientSockets.size(); i++) {
				std::cout << "READY READ" << std::endl;
				//HttpRequest Request;
				//while (Request.NeedParse()) {
					//Request.ReadRequest(server.ClientSockets[i]->fd);
					//if (Request.WaitBody()) {
						//Request.ReadBody(server.ClientSockets[i]->fd);
						////Если контент не удалось положить в переменную, то отправляем 413, надо еще прочитать, про 413 подробнее
					//}
				//}
				//Request.UpdateFirst();
				//HttpResponse Response(Request, server, server.ClientSockets[i]->fd);
				//Response.Response();

				//if (Request.NeedCloseConnect()) {
					//this->CloseConnection(server.FdSet, i);
					////need_erase = 1;
				//}
			}
		}
	}
	std::cout << "Сюда не должен был зайти" << std::endl;
}
