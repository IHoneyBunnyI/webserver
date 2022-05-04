#include "HttpResponse.hpp"

void HttpResponse::Get() {
	std::vector<Location> &locations = this->Server.locations;
	Location loc;
	//поиск подходящего location
	for (unsigned int i = 0; i < locations.size(); i++) {
		if (this->Path.find(locations[i].location) != std::string::npos) {
			loc = locations[i];
			std::cout << loc.location << std::endl;
			if (this->Path == loc.location) {
				break;
			}
			if (loc.location == "/") {
				continue;
			}
		}
	}
	//std::cout << loc.location << std::endl;
	//this->Error(this->ResponseStatus);
}
