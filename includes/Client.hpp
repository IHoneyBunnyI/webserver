#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <poll.h>
#include <iostream>
#define BUFSIZE (1 << 20)

class Client {
	private:
		pollfd* Socket;
		std::string Method;
		std::string Path;
		std::string Version;
		bool connected;
		bool full;

	public:
		Client();
		~Client();

		void SetSocket(pollfd *socket);
		void SetConnected(bool connected);
		bool Full();
		bool Connected();
		void Close();
		short Revents();
		int Fd();
		void ParseRequest(std::string buf);

};

#endif // CLIENT_HPP
