#include "webserv.hpp"
#include <fstream>

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
