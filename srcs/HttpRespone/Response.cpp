#include "HttpResponse.hpp"
#include <sys/socket.h>

bool enableMethod(std::vector<std::string> &methods, std::string &method);

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
			std::cout << location.location << std::endl;
			if (this->Path == location.location) {
				break;
			}
			if (location.location == "/") {
				continue;
			}
		}
	}
	//выкидываем 405 если метод не доступен
	if (!enableMethod(location.methods, this->Method)) {
		return (this->Error(405));
	}

	if (this->Method == "GET") {
		this->Get(location);
	} else if (this->Method == "POST") {
		this->Get(location);
	}
}

bool enableMethod(std::vector<std::string> &methods, std::string &method) {
	for (uint i = 0; i < methods.size(); i++) {
		if (methods[i] == method) {
			return true;
		}
	}
	return false;
}
