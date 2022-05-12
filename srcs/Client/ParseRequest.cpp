#include "Client.hpp"

void Client::ParseRequest(std::string buf) {
	std::string line;
	size_t index = buf.find('\n');
	while (index != std::string::npos) {
			line = buf.substr(0, index);
			buf = buf.substr(index + 1);
	}
	std::cout << "OSTATOK: "<< buf << std::endl;
}
