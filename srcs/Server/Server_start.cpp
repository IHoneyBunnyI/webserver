#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "Server.hpp"
#include "webserv.hpp"

void Server::start()
{
	log("Start Server");
	struct sockaddr_in socket_in;


	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)
	{
		log("socket not created");
		exit(1);
	}
	log("socket create");

	int on = 1;
	if ((setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0) //Разрешаем многократное использование дескриптора сокета
	{
		log("setsockopt() error");
		close(sock_fd);
		exit(1);
	}

	if ((fcntl(sock_fd, F_SETFL, O_NONBLOCK)) < 0) //Делаем сокет не блокирующим
	{
		log("fcntl() error");
		close(sock_fd);
		exit(1);
	}

	memset(&socket_in, 0, sizeof(socket_in));
	socket_in.sin_family = PF_INET;
	socket_in.sin_port = htons(SERVER_PORT); //Задаем порт, который будем слушать
	socket_in.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP

	if (bind(sock_fd, (const struct sockaddr *)&socket_in, sizeof(socket_in)) < 0) // связываем сокет с именем ??
	{
		log("bind() error");
		close(sock_fd);
		exit(1);
	}


	if ((listen(sock_fd, INT_MAX)) < 0) //Слушаем сокет, макс кол-во клиентов
	{
		log("listen() error");
		close(sock_fd);
		exit(1);
	}

	//int recv(int sockfd, void *buf, int len, int flags); //местный read 
	while (1)
	{

	}
	
	//close(sock_fd);
}
