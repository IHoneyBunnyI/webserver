#include "HttpRequest.hpp"

HtppRequest::HtppRequest():
	Method(""), Path(""), Version(""), close_connect(0){}

HtppRequest::~HtppRequest(){}

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
