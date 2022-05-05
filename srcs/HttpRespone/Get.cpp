#include "HttpResponse.hpp"
#include <fstream>
#include <sys/stat.h>

std::string getPathFile(Location &location, std::string &Path) {
	std::ifstream file;
	//тут нужно искать файл исходя из рута каждого location, но если его нет, нужно использовать стандартный
	//лучше эту проблему решать при парсинге location.root
	std::string pathFile = location.root + Path;
	//std::cout << "PATHFILE: " << pathFile << std::endl;
	file.open(pathFile);
	if (file.is_open()) {
		struct stat buf;
		std::memset(&buf, 0, sizeof(buf));
		stat(pathFile.c_str(), &buf);
		if (S_ISDIR(buf.st_mode)) {
			//std::cout << "OPEN" << std::endl;
			for (uint i = 0; i < location.indexes.size(); i++) { //поиск нужного файла, тк открытый файл является директорией
				std::string pathIndex = pathFile + "/" + location.indexes[i];
				std::ifstream index;
				//std::cout << "PATHINDEX: " << pathIndex << std::endl;
				index.open(pathIndex);
				if (index.is_open()) {
					return pathIndex;
				}
				//std::cout << "ERROR" << std::endl;
				return "";
			}
		} else {
			return pathFile;
		}
	}
	return "";
}

void HttpResponse::Get(Location &location) {
	// создаем стрим пытаемся открыть и если директория пробуем открыыть index, иначе открываем файл и отправляем
	std::string pathFile = getPathFile(location, this->Path);
	if (pathFile == "") {
		this->Error(404);
	}
	std::cout << pathFile << std::endl;
	std::string statusLine = GenStatusLine(200);
	std::string Headers = GenHeaders(pathFile);
	SendHttp(statusLine, Headers, pathFile);
	//std::cout << pathFile << std::endl;
}
