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

	memset(&socket_in, 0, sizeof(socket_in));
	socket_in.sin_family = PF_INET;
	socket_in.sin_port = htons(port); //Задаем порт, который будем слушать
	socket_in.sin_addr.s_addr = inet_addr(ip.c_str()); //IP

	if (bind(sock_fd, (const struct sockaddr *)&socket_in, sizeof(socket_in)) < 0) { // связываем сокет с адресом и портом
		Server::Log("bind() error");
		close(sock_fd);
	}

	if ((listen(sock_fd, -1)) < 0) { //Слушаем сокет
		Server::Log("listen() error");
		close(sock_fd);
	}
	return (sock_fd);
}

void Server::CreateServerSockets() {
	for (uint i = 0; i < this->servers.size(); i++) {
		for (uint j = 0; j < this->servers[i].ports.size(); j++) {
			int fd = createListenSocket(servers[i].ports[j], servers[i].server_names[j]);
			servers[i].FdSet.push_back((pollfd){fd, POLLIN, 0});
			servers[i].ServerSockets.push_back(&(servers[i].FdSet[j]));
		}
	}
}

