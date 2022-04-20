#include "HttpResponse.hpp"

void HttpResponse::Send() {
	//std::cout << this->BadRequest << std::endl;
	if (this->BadRequest != 0) {
		this->Error();
	} else if (this->Method == "GET") {
		this->Get();
	//} else if (this->Method == "POST") {
		//this->Post();
	//} else if (this->Method == "DELETE") {
		//this->Delete();
	}
}
