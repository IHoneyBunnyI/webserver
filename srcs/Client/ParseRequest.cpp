#include "Client.hpp"
#include "Parser.hpp"

void Client::ParseRequest(std::string buf) {
	//std::string line;
	std::cout << "NEW CALL" << std::endl;
	std::vector<std::string> lines;
	if (!this->Tmp.empty()) {
		buf = Tmp + buf;
		Tmp = "";
	}
	if (buf.find('\n') != std::string::npos) {
		lines = Parser::split(buf, "\n");
		if (buf[buf.length() - 1] != '\n') {
			this->Tmp = lines[lines.size() - 1];
			lines.erase(lines.end() - 1);
		}
	} else {
		this->Tmp = buf;
		return;
	}
	//std::cout << "NEW CALL" << std::endl;
	//std::cout << lines.size() << std::endl;
	for (uint i = 0; i < lines.size(); i++) {
		std::cout << "lines " << i << ") " << lines[i] << std::endl;
	}
	//while (buf.find('\n') != std::string::npos) {
		//line = buf.substr(0, buf.find('\n'));
		//buf = buf.substr(buf.find('\n'));
	//}
	//std::cout << "OSTATOK: "<< buf << std::endl;
}
