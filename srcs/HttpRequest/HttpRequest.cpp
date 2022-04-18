#include "HttpRequest.hpp"
#include <map>

HttpRequest::HttpRequest():
	Method(""),
	Path(""),
	Version(""),
	Headers(),
	CloseConnect(0),
	RequestLineExist(0),
	HeadersExist(0),
	BadRequest(0)
{}

HttpRequest::HttpRequest(const HttpRequest& ref):
	Method(ref.Method),
	Path(ref.Path),
	Version(ref.Version),
	Headers(ref.Headers),
	CloseConnect(ref.CloseConnect),
	RequestLineExist(ref.RequestLineExist),
	HeadersExist(ref.HeadersExist),
	BadRequest(ref.BadRequest)
{}

HttpRequest& HttpRequest::operator = (const HttpRequest& ref) {
	if (&ref != this) {
		this->Method = ref.Method;
		this->Path = ref.Path;
		this->Version = ref.Version;
		this->Headers = ref.Headers;
		this->CloseConnect = ref.CloseConnect;
		this->RequestLineExist = ref.RequestLineExist;
		this->HeadersExist = ref.HeadersExist;
		this->BadRequest = ref.BadRequest;
	}
	return *this;
}

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
void HttpRequest::SetCloseConnection(int CloseConnect) {
	this->CloseConnect = CloseConnect;
}

unsigned char HttpRequest::GetHeadersExist() {
	return (this->HeadersExist);
}

std::ostream& operator << (std::ostream& cout, const std::map<std::string, std::string> c) {

	std::map<std::string, std::string>::const_iterator begin = c.begin();
	std::map<std::string, std::string>::const_iterator end = c.end();
	cout << "{\n";
	for (; begin != end; begin++)
		cout << "\t" << begin->first << " : " << begin->second << std::endl;
	cout << "}";
	return (cout);
}
