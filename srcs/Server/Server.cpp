#include <fstream>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Server.hpp"
#include "webserv.hpp"
#include <arpa/inet.h>

Server::Server(): ports(0), sockets(0), request(""), fd_ip() {}
Server::~Server() {}

Server::Server(const Server& ref)
{
	this->ports = ref.ports;
	this->sockets = ref.sockets;
	this->request = ref.request;
	this->fd_ip = ref.fd_ip;
}

Server& Server::operator = (const Server& ref)
{
	if (this != &ref)
	{
		this->ports = ref.ports;
		this->sockets = ref.sockets;
		this->request = ref.request;
		this->fd_ip = ref.fd_ip;
	}
	return *this;
}

void Server::setPorts(std::vector<int> ports)
{
	this->ports = ports;
}

void Server::addPort(int port)
{
	this->ports.push_back(port);
}

void Server::openConnection(pollfd *fds, int &nfds, int i)
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
		this->fd_ip[fds[nfds].fd] = ip;
		nfds++;
	}
}

int Server::closeConnection(int &close_connect, pollfd *fds, int i)
{
		std::string ip = this->fd_ip[fds[i].fd];
		this->fd_ip.erase(fds[i].fd); // пока не очень понятно зачем, но пусть
		close_connect = 0;
		close(fds[i].fd);
		fds[i].fd = -1;
		log("Client with ip: " + ip + " disconnect");
		return 1;
}

std::string Server::readRequest(int fd, int &close_connect)
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
