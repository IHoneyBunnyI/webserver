#include "HttpResponse.hpp"

void HttpResponse::Get() {
	//std::string StatusLine;
	this->ResponseStatus = 404;
	this->Error();
	return;
}
