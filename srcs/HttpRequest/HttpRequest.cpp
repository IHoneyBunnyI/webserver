#include "HttpRequest.hpp"

HttpRequest::HttpRequest():
	Method(""), Path(""), Version(""), close_connect(0){}

HttpRequest::~HttpRequest(){}

std::string HttpRequest::GetMethod() {
	return (this->Method);
}

std::string HttpRequest::GetPath() {
	return (this->Path);
}

std::string HttpRequest::GetVersion() {
	return (this->Version);
}

std::map<std::string, std::string> HttpRequest::GetHeaders() {
	return (this->Headers);
}
