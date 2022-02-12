#include <fstream>
#include <sys/socket.h>
#include "Server.hpp"
#include "webserv.hpp"

std::string send_http(std::string html)
{
	std::string res =
	"HTTP/1.1 200 OK\r\n"
	"Content-Type: text/html; charset=UTF-8\r\n";
	res += "Content-Length: " + std::to_string(html.length());
	res += "\n\n";
	return res;
}

std::string get_file(std::string root, std::string path)
{
	std::string file;

	//std::cout << root << path << std::endl;
	std::ifstream stream(root + path);
	if (!stream)
		return "<h1>Error</h1>"; // Временный костыль
	while (stream)
	{
		std::string tmp;
		std::getline(stream, tmp);
		tmp += "\n";
		file += tmp;
	}
	//std::cout << YELLOW "file " << file << WHITE << std::endl;
	// Сейчас файл отправляется сразу весь, но это не правильно, в случае если подать серваку 
	// файл на Гиг или просто какой-то нереально большой, то все упадет, поэтому отправлять нужно кусками
	return (file);
}

std::string get_path_from_GET(std::string request) // временный костыль
{
	std::string::iterator begin = request.begin() + (request.find("/"));
	std::string::iterator end = request.begin() + request.find(" ", request.find("/")); // тут request.find возвраает npos
	//if (begin == end)
		//std::cout << "AAAAAAAAAAAAAAAAAA" << std::endl;
	std::string res(begin, end); // тут бага если дать через nc что-то с '/' без пробела
	return res;
}

void Server::GET(int fd)
{
	std::string path = get_path_from_GET(this->request); // Костыли
	if (path == "/")
		path = "/index.html";
	
	//генерируем ответ
	std::string html = get_file("./www", path);
	std::string headers = send_http(html);
	std::string response = headers + html;

	//Отправляем ответ
	if ((send(fd, response.c_str(), response.length(), 0)) < 0)
	{
		std::cout << "send() failed" << std::endl;
		close_connect = 1;
	}
	return;
}
