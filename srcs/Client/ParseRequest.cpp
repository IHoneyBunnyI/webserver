#include "Client.hpp"
#include "Parser.hpp"

void Client::ParseRequest(std::string buf) {
	std::string line;
	std::cout << "NEW CALL" << std::endl;
	//std::vector<std::string> lines;
	if (!this->Tmp.empty()) {
		buf = this->Tmp + buf;
		Tmp = "";
	}
	while (buf.find('\n') != std::string::npos) {
			line = buf.substr(0, buf.find('\n'));
			buf = buf.substr(buf.find('\n') + 1);
			if (line == "" || line == "\r") {
				this->full = true;
				break;
			}
			ParseLineFromRequest(line);
	}
	if (!buf.empty()) {
		this->Tmp = buf;
	}
}
