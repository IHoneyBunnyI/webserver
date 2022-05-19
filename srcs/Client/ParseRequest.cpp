#include "Client.hpp"
#include "Parser.hpp"

void Client::ParseRequest(std::string buf) {
	std::string line;
	if (!this->Tmp.empty()) {
		buf = this->Tmp + buf;
		Tmp = "";
	}
	if (!this->FullHeaders) {
		while (buf.find('\n') != std::string::npos) {
				line = buf.substr(0, buf.find('\n'));
				buf = buf.substr(buf.find('\n') + 1);
				if (line == "" || line == "\r") {
					this->FullHeaders = true;
					break;
				}
				ParseLineFromRequest(line);
		}
	}
	if (!buf.empty()) {
		this->Tmp = buf;
	}
	if (this->FullHeaders && (this->Headers.count("Content-Length") > 0 || this->Headers.count("Transfer-Encoding") > 0)) {
		this->ContentLength = static_cast<unsigned long>(std::stol(this->Headers["Content-Length"]));
		this->body = this->body + this->Tmp;
		if (this->body.size() > this->ClientMaxBodySize) {
			this->ResponseStatus = 413;
			this->body = "";
			this->full = true;
		}
		if (this->body.size() >= this->ContentLength) { //Проверям полностью ли дошел нам боди
			this->full = true;
			if (this->body.size() > this->ContentLength) { //Если боди пришло много отрезаем до ContentLength
				this->body = this->body.substr(0, this->ContentLength);
				//std::cout << "SIZE " << this->body.size() << std::endl;
				//std::cout << "BODY " << body << std::endl;
			}
		}
	} else if (this->FullHeaders) {
		this->full = true;
	}
}
