#include "HttpResponse.hpp"
#include <sys/socket.h>

void HttpResponse::Send() {
	std::cout << this->BadRequest << std::endl;
	if (this->BadRequest != 0) {
		this->Error();
	} else if (this->Method == "GET") {
		this->Get();
	} else  {
		if ((send(this->fd, "request accepted\n", 17, 0)) < 0) {
			std::cout << "send() failed" << std::endl;
		}
	}
	//} else if (this->Method == "POST") {
		//this->Post();
	//} else if (this->Method == "DELETE") {
		//this->Delete();
	
}
