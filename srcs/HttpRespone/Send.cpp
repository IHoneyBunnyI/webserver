#include "HttpResponse.hpp"

void HttpResponse::Send() {
	if (this->BadRequest != 0) {
		this->Error();
	} else if (this->Method == "GET") {
		this->Get();
	} else if (this->Method == "POST") {
		this->Post();
	} else if (this->Method == "DELETE") {
		this->Delete();
	}
}
