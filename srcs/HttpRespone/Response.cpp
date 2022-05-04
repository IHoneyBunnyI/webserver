#include "HttpResponse.hpp"
#include <sys/socket.h>
#include <fstream>
#include <sys/stat.h>

void HttpResponse::Response() {
	if (this->ResponseStatus != 0) {
		return (this->Error(this->ResponseStatus));
	}

	std::vector<Location> &locations = this->Server.locations;
	Location location;
	//поиск подходящего location
	//нужно сделать умный проход по всем location'ам
	for (uint i = 0; i < locations.size(); i++) {
		if (this->Path.find(locations[i].location) != std::string::npos) {
			location = locations[i];
			//std::cout << location.location << std::endl;
			if (this->Path == location.location) {
				break;
			}
			if (location.location == "/") {
				continue;
			}
		}
	}
	//проверка на то, можно ли в этом location использовать данный метод
	uint enableMethod = 0;
	for (uint i = 0; i < location.methods.size(); i++) {
		if (location.methods[i] == this->Method) {
			enableMethod = 1;
			break;
		}
	}
	if (!enableMethod) {
		//this->ResponseStatus = 405;
		return (this->Error(405));
	}

	// создаем стрим пытаемся открыть и если директория пробуем открыыть index, иначе открываем файл и отправляем
	std::ifstream file;
	file.open(location.root + this->Path);
	if (file.is_open()) {
		std::cout << "OPEN" << std::endl;
		struct stat buf;
		std::memset(&buf, 0, sizeof(buf));
		stat((location.root + this->Path).c_str(), &buf);
		if (S_ISDIR(buf.st_mode)) {
			std::cout << "IS DIR" << std::endl;
			std::ifstream index;
			//тут надо найти существующий индекс и вернуть его 
			//std::string indexPath = findIndex(location.indexes);
			//index.open(location.root + this->Path + indexPath);
			//пробуем открыть index в этой dir
		} else {
			std::cout << "IS NOT DIR" << std::endl;
			//пробуем открыть этот файл 
		}
	}
	else {
		std::cout << "NOT OPEN" << std::endl;
		this->Error(404);
	}
}
