#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <poll.h>

class Client {

public:
	Client();

	pollfd* clientSocket;
	bool connected;
	bool full;
};

#endif // CLIENT_HPP
