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
	Server::Log("Start Server");
	while (1) {
		int need_erase = 0;
		int rpoll = 0;
		for (uint serverNum = 0; serverNum < this->servers.size(); serverNum++) {
			//std::cout << serverNum << std::endl;
			ServerConfig &server = this->servers[serverNum]; // ссоздаю ссылку на данный сервер, обращаться буду через нее

			rpoll = poll(server.fds.data(), server.fds.size(), 0);
			if (rpoll <= 0) { //POLL Error 
				continue;
			}
			//сделали poll, идем по всем сокетам сервера, если в нем есть события открываем новый сокет, далее идем по всем открытым сокетам и читаем
			uint current_size = server.fds.size();
			for (uint i = 0; i < current_size; i++){
				if (server.fds[i].revents == 0) {
					continue;
				}
				if (std::find(server.sockets.begin(), server.sockets.end(), server.fds[i].fd) != server.sockets.end()) {
					this->OpenConnection(server, i);
				} else {
					HttpRequest Request;
					while (Request.NeedParse()) {
						Request.ReadRequest(server.fds[i].fd);
						if (Request.WaitBody()) {
							Request.ReadBody(server.fds[i].fd);
							//Если контент не удалось положить в переменную, то отправляем 413, надо еще прочитать, про 413 подробнее
						}
					}
					Request.UpdateFirst();
					HttpResponse Response(Request, server, server.fds[i].fd);
					Response.Response();

					if (Request.NeedCloseConnect()) {
						this->CloseConnection(server.fds, i);
						need_erase = 1;
					}
				}
			}
			if (need_erase) {
				erase_fds(server.fds);
				need_erase = 0;
			}
		}
		usleep(10);
	}
}
