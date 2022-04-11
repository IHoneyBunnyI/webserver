#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Server.hpp"
#include <arpa/inet.h>
#include <fcntl.h>
#include "webserv.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

void erase_fds(std::vector<pollfd> &fds) {

	for (std::size_t i = 0; i < fds.size(); i++) {
		if (fds[i].fd == -1)
			fds.erase(fds.begin() + i);
	}
}

static int create_listen_socket(int port)
{
	struct sockaddr_in socket_in;

	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1){
		Server::Log("socket not created");
	}
	Server::Log("Socket create");

	int on = 1;
	if ((setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0) { //Разрешаем многократное использование дескриптора сокета
		Server::Log("setsockopt() error");
		close(sock_fd);
	}

	if ((fcntl(sock_fd, F_SETFL, O_NONBLOCK)) < 0) { //Делаем сокет не блокирующим
		Server::Log("fcntl() error");
		close(sock_fd);
	}

	memset(&socket_in, 0, sizeof(socket_in));
	socket_in.sin_family = PF_INET;
	socket_in.sin_port = htons(port); //Задаем порт, который будем слушать
	socket_in.sin_addr.s_addr = inet_addr("0.0.0.0"); //IP

	if (bind(sock_fd, (const struct sockaddr *)&socket_in, sizeof(socket_in)) < 0) { // связываем сокет с именем ??
		Server::Log("bind() error");
		close(sock_fd);
	}

	if ((listen(sock_fd, 1024)) < 0) { //Слушаем сокет
		Server::Log("listen() error");
		close(sock_fd);
	}
	return (sock_fd);
}

static void openConnection(std::vector<pollfd> &fds, int i, std::map<int, std::string> &fd_ip)
{
	struct sockaddr_in in;
	socklen_t len_in = sizeof(in);

	int new_sd = 0;
	while (new_sd != -1)
	{
		new_sd = accept(fds[i].fd, (sockaddr *)&in, &len_in); // тут на счет 1 параметра не уверен до конца
		if (new_sd < 0)
			break;
		pollfd fd;
		fd.fd = new_sd;
		fd.events = POLLIN;
		//std::cout << GREEN "New connection with fd: " << new_sd << WHITE << std::endl;
		fds.push_back(fd);

		char bits[100];
		memset(&bits, 0, sizeof(bits));
		inet_ntop(in.sin_family, &in.sin_addr, bits, sizeof(bits));
		std::string ip(bits);
		Server::Log("Client with ip: " + ip + " and fd: " + std::to_string(new_sd) + " connected");
		fd_ip[fds[fds.size() - 1].fd] = ip;
	}
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
	for (std::vector<int>::iterator begin = this->ports.begin(); begin != this->ports.end(); begin++) //превращаем спаршенные сокеты в открытые порты 
		this->sockets.push_back(create_listen_socket(*begin));
	for (std::vector<int>::iterator begin = this->sockets.begin(); begin != this->sockets.end(); begin++)
		fds.push_back((pollfd){*begin, POLLIN, 0});

	//int close_connect = 0;
	int need_erase = 0;
	int rpoll = 0;
	while (1) {
		rpoll = poll(fds.data(), fds.size(), -1);
		if (rpoll <= 0) //POLL Error
			continue;
		unsigned int current_size = fds.size();
		for (unsigned int i = 0; i < current_size; i++){
			if (fds[i].revents == 0)
				continue;
			else if (std::find(this->sockets.begin(), this->sockets.end(), fds[i].fd) != this->sockets.end()) {
				openConnection(fds, i, this->fd_ip);
			} else {
				HtppRequest htppRequest;
				std::string line;
				while (line != "\r\n") {
					line = htppRequest.ReadRequest(fds[i].fd);
					htppRequest.ParseRequest(line);
				}
				//GET(fds[i].fd, rpoll, "GET / HTTP/1.1\n");
				//GET(fds[i].fd, rpoll, "GET /favicon/favicon.ico HTTP/1.1\n");
				//std::cout << RED "END REQUEST!!" WHITE << std::endl;
				if (htppRequest.NeedCloseConnect()) {
					std::cout << "AAA" << std::endl;
					need_erase = closeConnection(fds, i, this->fd_ip);
				} else {
					HtppResponse htppResponse(htppRequest);
				}
			}
		}
		if (need_erase) {
			erase_fds(fds);
			need_erase = 0;
		}
	}
}
