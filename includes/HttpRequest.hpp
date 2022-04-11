#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <iostream>
#include <map>

class HtppRequest {
private:
	HtppRequest(const HtppRequest& ref);
	HtppRequest& operator = (const HtppRequest& ref);

	std::string Request;
	std::string Method;
	std::string Path;
	std::string Version;
	std::map<std::string, std::string> Headers;
	int close_connect;
	//все хэдэры в реализации не нуждаются, только HTPP/1.1
public:
	HtppRequest();
	~HtppRequest();

	std::string GetRequest();
	std::string GetMethod();
	std::string GetPath();
	std::string GetVersion();
	int NeedCloseConnect();
	std::map<std::string, std::string> GetHeaders();

	void ParseRequest(std::string line);
	std::string ReadRequest(int fd);
	//void ReadRequest(int &close_connect, int fd);
};

#endif
