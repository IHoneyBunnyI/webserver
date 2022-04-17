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
	//while (new_sd != -1)
	//{
		new_sd = accept(server.fds[i].fd, (sockaddr *)&in, &len_in); 
		if (new_sd < 0)
			return "";
		pollfd fd;
		fd.fd = new_sd;
		fd.events = POLLIN;
		std::cout << GREEN "New connection with fd: " << new_sd << WHITE << std::endl;
		server.fds.push_back(fd);

		char bits[100];
		memset(&bits, 0, sizeof(bits));
		inet_ntop(in.sin_family, &in.sin_addr, bits, sizeof(bits));
		std::string ip(bits);
		Server::Log("Client with ip: " + ip + " and fd: " + std::to_string(new_sd) + " connected");
		//fd_ip[server.fds[server.fds.size() - 1].fd] = ip;
		return ip;
	//}
}

static int closeConnection(std::vector<pollfd> &fds, int i, std::map<int, std::string> &fd_ip)
{
		std::string ip = fd_ip[fds[i].fd];
		Server::Log("Client with ip: " + ip + " and fd: " + std::to_string(fds[i].fd) + " disconnect");
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

			rpoll = poll(server.fds.data(), server.fds.size(), 100);
			if (rpoll <= 0) { //POLL Error 
				Server::Log("Poll error");
				continue;
			}
			unsigned int current_size = server.fds.size();
			for (unsigned int i = 0; i < current_size; i++){
				if (server.fds[i].revents == 0) {
					continue;
				}
				if (std::find(server.sockets.begin(), server.sockets.end(), server.fds[i].fd) != server.sockets.end()) {
					std::string ip = openConnection(server, i);
					fd_ip[server.fds[server.fds.size() - 1].fd] = ip;
				} else {
					HttpRequest httpRequest;
					std::string line;
					int end = 0;
					while (!end && httpRequest.NeedCloseConnect() == 0) { // на счет 2 условия пока не уверен
						line = httpRequest.ReadRequest(server.fds[i].fd);
						if (line == "\r\n" || line == "\n")
							end = 1;
						httpRequest.ParseRequest(line);
					}
					if (httpRequest.GetMethod() != "") {
						std::cout << YELLOW << httpRequest.GetMethod() << WHITE << std::endl;
						std::cout << YELLOW << httpRequest.GetPath() << WHITE << std::endl;
						std::cout << YELLOW << httpRequest.GetVersion() << WHITE << std::endl;
					}
					//GET(fds[i].fd, rpoll, "GET / HTTP/1.1\n");
					//GET(fds[i].fd, rpoll, "GET /favicon/favicon.ico HTTP/1.1\n");
					//std::cout << RED "END REQUEST!!" WHITE << std::endl;
					if (httpRequest.NeedCloseConnect()) {
						need_erase = closeConnection(server.fds, i, this->fd_ip);
					} else {
						HtppResponse htppResponse(httpRequest);
					}
				}
			}
			if (need_erase) {
				erase_fds(server.fds);
				need_erase = 0;
			}
		}
	}
}
