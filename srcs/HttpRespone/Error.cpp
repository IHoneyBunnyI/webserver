#include "HttpResponse.hpp"
#include <fstream>
#include <sys/socket.h>

unsigned long long lengthFile(std::string path) {
	unsigned long long length = 0;

	std::string file;
	std::ifstream stream(path);
	while (stream)
	{
		std::string line;
		std::getline(stream, line);
		if (line == "")
			break;
		line += "\n";
		length += line.length();
	}
	return length;
}

std::string GenHeaders(std::string path) {
	std::string Headers;
	Headers += "Server: webserver\n";
	Headers += "Content-Type: text/html\n";
	Headers += "Content-Length: " + std::to_string(lengthFile(path)) + "\n";
	Headers += "Connection: close\n\n";
	return Headers;
}

void HttpResponse::Error(int ResponseStatus) {
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
	if (path_file.empty()) {
		this->SendDefaultError(ResponseStatus);
		return;
	} else {
		file.open(path_file);
		//если  файл не открывается по каким либо причинам отправляем дефолт
		if (!file) {
			this->SendDefaultError(ResponseStatus);
			return;
		} else { // иначе закрываем зная, что он открывается и генерируем хэдеры
			file.close();
		}
	}
	
	std::string StatusLine = GenStatusLine(ResponseStatus);
	std::string Headers = GenHeaders(path_file);
	SendHttp(StatusLine, Headers, path_file);
}
