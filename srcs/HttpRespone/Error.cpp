#include "HttpResponse.hpp"
#include <sys/socket.h>
#include <fstream>

void sendFile(int fd, std::string path) {

	std::ifstream stream(path);
	if (!stream) {
		std::string file = "\
<html>\n\
<head><title>400 Bad Request</title></head>\n\
<body>\n\
<center><h1>400 Bad Request</h1></center>\n\
<hr><center>Webserver</center>\n\
</body>\n\
</html>\n\n";
		if ((send(fd, file.c_str(), file.length(), 0)) < 0) {
			std::cout << "send() failed" << std::endl;
		}
	}
	while (stream)
	{
		std::string line;
		std::getline(stream, line);
		line += "\n";
		if ((send(fd, line.c_str(), line.length(), 0)) < 0) {
			std::cout << "send() failed" << std::endl;
		}
	}
}

int needRelativePath(std::string path) {
	if (path[0] == '/' || (path[0] == '.' && path[1] == '/'))
		return 0;
	return 1;
}

unsigned long long lengthFile(std::string path) {
	unsigned long long length = 0;

	std::string file;
	if (needRelativePath(path)) {
		path = "./" + path;
	}
	std::ifstream stream(path);
	if (!stream) {
		return 148; // Временный костыль
	}
	while (stream)
	{
		std::string line;
		std::getline(stream, line);
		line += "\n";
		length += line.length();
	}
	return length;
}

void HttpResponse::Error() {
	std::string statusLine;
	std::string Headers;
	std::string path_file;
	std::string file;
	for (unsigned int i = 0; i < this->Server.error_pages.size(); i++) {
		for (unsigned int j = 0; j < this->Server.error_pages[i].errors.size(); j++) {
			if (this->Server.error_pages[i].errors[j] == this->BadRequest) {
				path_file = this->Server.error_pages[i].error_page;
				this->CloseConnect = 1;
			}
		}
	}
	
	if (path_file.empty()) {

	}

	statusLine += "HTTP/1.1 ";
	statusLine += std::to_string(this->BadRequest) + " ";
	if (this->BadRequest == 400) {
		statusLine += "Bad Request\n";
	} else if (this->BadRequest == 404) {
		statusLine += "Not Found\n";
	}

	//также если не нашелся надо что-то делать
	Headers += "Server: webserver\n";
	Headers += "Content-Type: text/html\n";
	Headers += "Connection: close\n";
	Headers += "Content-Length: " + std::to_string(lengthFile(path_file)) + "\n";
	Headers += "\n";

	if ((send(fd, statusLine.c_str(), statusLine.length(), 0)) < 0) {
		std::cout << "send() failed" << std::endl;
	}
	if ((send(fd, Headers.c_str(), Headers.length(), 0)) < 0) {
		std::cout << "send() failed" << std::endl;
	}
	sendFile(fd, path_file);
}
