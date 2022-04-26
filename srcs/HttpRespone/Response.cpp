#include "HttpResponse.hpp"
#include <sys/socket.h>

void HttpResponse::Response() {
	if (this->ResponseStatus != 0) {
		this->Error();
	} else if (this->Method == "GET") {
		this->Get();
	} else  {
		if ((send(this->fd, "request accepted\n", 17, 0)) < 0) {
			std::cout << "send() failed" << std::endl;
			this->CloseConnect = 1;
		}
	}
	//this->ResponseStatus = 0;
	//} else if (this->Method == "POST") {
		//this->Post();
	//} else if (this->Method == "DELETE") {
		//this->Delete();
	
}
