#include <poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
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


static std::string openConnection(ServerConfig &server, int i)
{
	struct sockaddr_in in;
	socklen_t len_in = sizeof(in);

	int new_sd = 0;
		new_sd = accept(server.fds[i].fd, (sockaddr *)&in, &len_in); 
		if (new_sd < 0)
			return "";
		pollfd fd;
		fd.fd = new_sd;
		fd.events = POLLIN;
		//std::cout << GREEN "New connection with fd: " << new_sd << WHITE << std::endl;
		server.fds.push_back(fd);

		char bits[100];
		memset(&bits, 0, sizeof(bits));
		inet_ntop(in.sin_family, &in.sin_addr, bits, sizeof(bits));
		std::string ip(bits);
		Server::Log("Client with ip: " + ip + " and fd: " + std::to_string(new_sd) + " connected");
		return ip;
}

static int closeConnection(std::vector<pollfd> &fds, int i, std::map<int, std::string> &fd_ip)
{
		std::string ip = fd_ip[fds[i].fd];
		Server::Log("Client with ip: " + ip + " and fd: " + std::to_string(fds[i].fd) + " disconnect");
		//std::cout << RED "Disconnect with fd: " << fds[i].fd << WHITE << std::endl;
		fd_ip.erase(fds[i].fd); // пока не очень понятно зачем, но пусть
		close(fds[i].fd);
		fds[i].fd = -1;
		return 1;
}

void Server::Start() {
	Server::Log("Start Server");
	while (1) {
		int need_erase = 0;
		int rpoll = 0;
		for (unsigned int serverNum = 0; serverNum < this->servers.size(); serverNum++) {
			//std::cout << serverNum << std::endl;
			ServerConfig &server = this->servers[serverNum]; // ссоздаю ссылку на данный сервер, обращаться буду через нее

			rpoll = poll(server.fds.data(), server.fds.size(), 0);
			if (rpoll <= 0) { //POLL Error 
				continue;
			}
			unsigned int current_size = server.fds.size();
			for (unsigned int i = 0; i < current_size; i++){
				if (server.fds[i].events == 0) {
					continue;
				}
				if (std::find(server.sockets.begin(), server.sockets.end(), server.fds[i].fd) != server.sockets.end()) {
					std::string ip = openConnection(server, i);
					fd_ip[server.fds[server.fds.size() - 1].fd] = ip;
				} else {
					HttpRequest Request;
					std::string line;
					while (Request.NeedParse()) {
						line = Request.ReadRequest(server.fds[i].fd);
						if (Request.WaitBody()) {
							Request.ReadBody(server.fds[i].fd);
							//Если контент не удалось положить в переменную, то отправляем 413, надо еще прочитать, про 413 подробнее
						}
					}
					Request.UpdateFirst();
					HttpResponse Response(Request, server, server.fds[i].fd);
					Response.Response();

					if (Request.NeedCloseConnect() || line.empty()) {
						need_erase = closeConnection(server.fds, i, this->fd_ip);
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
