#include <fstream>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Server.hpp"
#include <arpa/inet.h>
#include <fcntl.h>
#include "webserv.hpp"

Server::Server(): ports(0), sockets(0), fd_ip() {}
Server::~Server() {}

Server::Server(const Server& ref)
{
	this->ports = ref.ports;
	this->sockets = ref.sockets;
	this->fd_ip = ref.fd_ip;
}

Server& Server::operator = (const Server& ref)
{
	if (this != &ref)
	{
		this->ports = ref.ports;
		this->sockets = ref.sockets;
		this->fd_ip = ref.fd_ip;
	}
	return *this;
}

void Server::setPorts(std::vector<int> ports)
{
	this->ports = ports;
}

void Server::AddPort(int port)
{
	this->ports.push_back(port);
}

static int compress_array(pollfd *fds, int &nfds)
{
	for (int i = 0; i < nfds; i++)
	{
		if (fds[i].fd == -1)
		{
			for(int j = i; j < nfds-1; j++)
				fds[j].fd = fds[j+1].fd;
			i--;
			nfds--;
		}
	}
	return 1;
}

static int create_listen_socket(int port)
{
	struct sockaddr_in socket_in;

	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)
	{
		log("socket not created");
		exit(1);
	}
	log("Socket create");

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
	socket_in.sin_port = htons(port); //Задаем порт, который будем слушать
	socket_in.sin_addr.s_addr = inet_addr("0.0.0.0"); //IP

	if (bind(sock_fd, (const struct sockaddr *)&socket_in, sizeof(socket_in)) < 0) // связываем сокет с именем ??
	{
		log("bind() error");
		close(sock_fd);
		exit(1);
	}

	if ((listen(sock_fd, 1024)) < 0) //Слушаем сокет
	{
		log("listen() error");
		close(sock_fd);
		exit(1);
	}
	return (sock_fd);
}

static void openConnection(pollfd *fds, int &nfds, int i, std::map<int, std::string> &fd_ip)
{

	struct sockaddr_in in;
	socklen_t len_in = sizeof(in);

	int new_sd = 0;
	while (new_sd != -1)
	{
		new_sd = accept(fds[i].fd, (sockaddr *)&in, &len_in); // тут на счет 1 параметра не уверен до конца
		if (new_sd < 0)
			break;
		fds[nfds].fd = new_sd;
		//std::cout << GREEN "New connection with fd: " << new_sd << WHITE << std::endl;
		fds[nfds].events = POLLIN;

		char bits[100];
		memset(&bits, 0, sizeof(bits));
		inet_ntop(in.sin_family, &in.sin_addr, bits, sizeof(bits));
		std::string ip(bits);
		log("Client with ip: " + ip + " connect");
		fd_ip[fds[nfds].fd] = ip;
		nfds++;
	}
}

static int closeConnection(int &close_connect, pollfd *fds, int i, std::map<int, std::string> &fd_ip)
{
		std::string ip = fd_ip[fds[i].fd];
		fd_ip.erase(fds[i].fd); // пока не очень понятно зачем, но пусть
		close_connect = 0;
		close(fds[i].fd);
		fds[i].fd = -1;
		log("Client with ip: " + ip + " disconnect");
		return 1;
}

static std::string readRequest(int fd, int &close_connect)
{
	std::string res;
	char buffer[1000];
	memset(buffer, 0, 1000);
	close_connect = 0;
	while (1)
	{
		int rc = recv(fd, buffer, sizeof(buffer), 0);
		if (rc < 0)
			break; //full data read
		if (rc == 0)
		{
			close_connect = 1;
			break;
		}
		res += buffer;
		memset(buffer, 0, 1000);
	}
	return res;
}

void Server::Start()
{
	log("Start Server");
	for (std::vector<int>::iterator begin = this->ports.begin(); begin != this->ports.end(); begin++) //превращаем спаршенные сокеты в открытые порты 
		this->sockets.push_back(create_listen_socket(*begin));
	//pollfd fds[1000];
	memset(fds, 0 , sizeof(fds));
	int nfds = this->sockets.size();
	int i = 0;
	for (std::vector<int>::iterator begin = this->sockets.begin(); begin != this->sockets.end(); begin++)
	{
		fds[i].fd = *begin;
		fds[i].events = POLLIN;
		i++;
	}

	int close_connect = 0;
	int need_compress_array = 0;
	int rpoll = 0;
	while (1) {
		rpoll = poll(fds, nfds, -1);
		if (rpoll <= 0) //POLL Error
			continue;
		unsigned int current_size = nfds;
		for (unsigned int i = 0; i < current_size; i++){
			if (fds[i].revents == 0)
				continue;
			else if (std::find(this->sockets.begin(), this->sockets.end(), fds[i].fd) != this->sockets.end()) {
				openConnection(fds, nfds, i, this->fd_ip);
			} else {
				//читаем запрос
				std::string request = readRequest(fds[i].fd, close_connect); //вероятно для очень больших запросов эта штука не подойдет 

				//
				// Тут в дело вступет HttpRequest (Ralverta)
				//

				//если GET получаем файл
				std::string http_method = "GET";
				if (http_method == "GET")
					this->GET(fds[i].fd, close_connect, request);

				if (close_connect)
					need_compress_array = closeConnection(close_connect, fds, i, this->fd_ip);
			}
		}
		if (need_compress_array) {
			need_compress_array = compress_array(fds, nfds);
		}
	}
}
