#include "HttpResponse.hpp"
#include <fstream>
#include <sys/socket.h>

void sendFile(int fd, std::string path) {

	std::ifstream stream(path);
	while (stream)
	{
		std::string line;
		std::getline(stream, line);
		if (line.empty())
			return;
		line += "\n";
		if ((send(fd, line.c_str(), line.length(), 0)) <= 0) {
			std::cout << "send() failed" << std::endl;
		}
	}
}

unsigned long long lengthFile(std::string path) {
	unsigned long long length = 0;

	std::string file;
	std::ifstream stream(path);
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
	std::string path_file;
	//закрываем соедениение и ищем файл из дефолтных
	this->CloseConnect = 1;
	for (unsigned int i = 0; i < this->Server.error_pages.size(); i++) {
		for (unsigned int j = 0; j < this->Server.error_pages[i].errors.size(); j++) {
			if (this->Server.error_pages[i].errors[j] == this->ResponseStatus) {
				path_file = this->Server.error_pages[i].error_page;
			}
		}
	}
	
	//если файла не нашлось отправляем стандартную ошибку
	std::ifstream file;
	//this->ResponseStatus = 405;
	if (path_file.empty()) {
		this->SendDefaultError(this->fd, this->ResponseStatus);
		return;
	} else {
		file.open(path_file);
		//если  файл не открывается по каким либо причинам отправляем дефолт
		if (!file) {
			this->SendDefaultError(this->fd, this->ResponseStatus);
			return;
		} else { // иначе закрываем зная, что он открывается и генерируем хэдеры
			file.close();
		}
	}

	//std::string Headers = GenHeaders(path_file);

	//также если не нашелся надо что-то делать
	////Headers += "Content-Length: " + std::to_string(lengthFile(path_file)) + "\n";
	//Headers += "Content-Length: " + std::to_string(lengthFile(path_file)) + "\n";
	//Headers += "\n";

	//if ((send(fd, statusLine.c_str(), statusLine.length(), 0)) <= 0) {
		//std::cout << "send() failed" << std::endl;
		//this->CloseConnect = 1;
	//}
	//if ((send(fd, Headers.c_str(), Headers.length(), 0)) <= 0) {
		//std::cout << "send() failed" << std::endl;
		//this->CloseConnect = 1;
	//}
	//sendFile(fd, path_file);
}
