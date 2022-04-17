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
	int close_connect;
	//все хэдэры в реализации не нуждаются, только HTPP/1.1
public:
	HttpRequest();
	~HttpRequest();

	std::string GetRequest();
	std::string GetMethod();
	std::string GetPath();
	std::string GetVersion();
	int NeedCloseConnect();
	std::map<std::string, std::string> GetHeaders();

	void ParseRequest(std::string line);
	std::string ReadRequest(int fd);
};

#endif
