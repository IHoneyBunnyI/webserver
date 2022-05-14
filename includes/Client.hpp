#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <poll.h>
#include <iostream>
#include <map>
#define BUFSIZE (1 << 20)
//#define BUFSIZE (3)

class Client {
	private:
		pollfd* Socket;
		std::string Method;
		std::string Path;
		std::string Version;
		std::string Tmp;
		std::map<std::string, std::string> Headers;
		uint ResponseStatus;
		bool connected;
		bool full;
		bool FirstRequestLineExist;

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
		void ParseLineFromRequest(std::string line);
		void FirstRequestLine(std::string line);

};

#endif // CLIENT_HPP
