#include "HttpRequest.hpp"

HtppRequest::HtppRequest(std::string Request):
	Request(Request){}

HtppRequest::~HtppRequest(){}

std::string HtppRequest::GetRequest() {
	return (this->Request);
}

std::string HtppRequest::GetMethod() {
	return (this->Method);
}

std::string HtppRequest::GetPath() {
	return (this->Path);
}

std::string HtppRequest::GetVersion() {
	return (this->Version);
}

std::map<std::string, std::string> HtppRequest::GetHeaders() {
	return (this->Headers);
}
