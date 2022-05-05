#include "HttpRequest.hpp"
#include "webserv.hpp"
#include <map>

HttpRequest::HttpRequest():
	Method(""),
	Path(""),
	Version(""),
	Headers(),
	CloseConnect(false),
	RequestLineExist(false),
	HeadersExist(false),
	ResponseStatus(0),
	State(0),
	First(0)
{}

HttpRequest::HttpRequest(const HttpRequest& ref):
	Method(ref.Method),
	Path(ref.Path),
	Version(ref.Version),
	Headers(ref.Headers),
	CloseConnect(ref.CloseConnect),
	RequestLineExist(ref.RequestLineExist),
	HeadersExist(ref.HeadersExist),
	ResponseStatus(ref.ResponseStatus),
	State(ref.State),
	First(ref.First)
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
		this->ResponseStatus = ref.ResponseStatus;
		this->State = ref.State;
		this->First = ref.First;
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

bool HttpRequest::GetHeadersExist() {
	return (this->HeadersExist);
}

bool HttpRequest::NeedParse() {
	if (this->State == ALL) {
		return false;
	}
	return true;
}

bool HttpRequest::WaitBody() {
	if (this->State == NEED_BODY) {
		this->State = ALL;
		return true;
	}
	return false;
}

void HttpRequest::UpdateFirst() {
	this->First = 0;
}

int HttpRequest::GetResponseStatus() {
	return this->ResponseStatus;
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
