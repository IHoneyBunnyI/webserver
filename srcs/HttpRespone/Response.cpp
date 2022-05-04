#include "HttpResponse.hpp"
#include <sys/socket.h>

void HttpResponse::Response() {
	if (this->ResponseStatus != 0) {
		this->Error(this->ResponseStatus);
	} else if (this->Method == "GET") {
		this->Get();
	} else  {
		std::cout << "ACCEPT" << std::endl;
	}
	//this->ResponseStatus = 0;
	//} else if (this->Method == "POST") {
		//this->Post();
	//} else if (this->Method == "DELETE") {
		//this->Delete();
	
}
