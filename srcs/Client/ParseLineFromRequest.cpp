#include "Client.hpp"

void Client::ParseLineFromRequest(std::string line) {
	if (!this->FirstRequestLineExist) {
		FirstRequestLine(line);
	} else {
		AddHeader(line);
	}
}
