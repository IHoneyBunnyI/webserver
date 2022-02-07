#include "Server.hpp"
#include <sys/socket.h>

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
