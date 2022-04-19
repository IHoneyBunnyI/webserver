#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <iostream>
#include <map>

class HttpRequest {
private:
	HttpRequest(const HttpRequest& ref);
	HttpRequest& operator = (const HttpRequest& ref);

	std::string Method;
	std::string Path;
	std::string Version;
	std::map<std::string, std::string> Headers;
	std::string Body;
	int CloseConnect;
	unsigned char RequestLineExist;
	unsigned char HeadersExist;
	unsigned int BadRequest;
	//все хэдэры в реализации не нуждаются, только HTPP/1.1
public:
	HttpRequest();
	~HttpRequest();

	std::string GetRequest();
	std::string GetMethod();
	std::string GetPath();
	std::string GetVersion();
	unsigned char GetHeadersExist();
	int NeedCloseConnect();
	void SetCloseConnection(int CloseConnect);
	std::map<std::string, std::string> GetHeaders();

	void ParseRequest(std::string line);
	void RequestLine(std::string line);
	void AddHeader(std::string line);
	std::string ReadRequest(int fd, int &ReadRequest);
	void ReadBody(int fd);
};

std::ostream& operator << (std::ostream& cout, const std::map<std::string, std::string> c);

#endif
