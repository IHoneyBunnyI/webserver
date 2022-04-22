#include "Server.hpp"
#include "ServerConfig.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

static int createListenSocket(int port, std::string ip)
{
	struct sockaddr_in socket_in;

	int sock_fd = socket(AF_INET, SOCK_STREAM, 0); // создаю сокет
	if (sock_fd == -1){
		Server::Log("socket not created");
	}

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
	socket_in.sin_addr.s_addr = inet_addr(ip.c_str()); //IP

	if (bind(sock_fd, (const struct sockaddr *)&socket_in, sizeof(socket_in)) < 0) { // связываем сокет с адрессом и портом
		Server::Log("bind() error");
		close(sock_fd);
	}

	if ((listen(sock_fd, -1)) < 0) { //Слушаем сокет
		Server::Log("listen() error");
		close(sock_fd);
	}
	return (sock_fd);
}

void Server::CreateListenSockets() {
	for (unsigned int i = 0; i < this->servers.size(); i++) {
		for (unsigned int j = 0; j < this->servers[i].ports.size(); j++) {
			servers[i].sockets.push_back(createListenSocket(servers[i].ports[j], servers[i].ips[j]));
			Server::Log("Socket create with PORT: " + std::to_string(servers[i].ports[j]) + " IP: " + servers[i].ips[j]);
		}
	}
	for (unsigned int i = 0; i < this->servers.size(); i++) {
		for (unsigned int j = 0; j < this->servers[i].ports.size(); j++) {
			servers[i].fds.push_back((pollfd){servers[i].sockets[j], POLLIN, 0});
		}
	}
}

