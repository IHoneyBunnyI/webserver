#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <poll.h>
#include <iostream>

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

};

#endif // CLIENT_HPP
