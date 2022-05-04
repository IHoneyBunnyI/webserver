#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <iostream>
#include <map>

class HttpRequest {
	friend class HttpResponse;
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
		int ResponseStatus;
		uint State;
		uint First;
		//все хэдэры в реализации не нуждаются, только HTPP/1.1
	public:
		HttpRequest();
		~HttpRequest();

		std::string GetRequest();
		std::string GetMethod();
		std::string GetPath();
		std::string GetVersion();
		void UpdateFirst();
		unsigned char GetHeadersExist();
		int GetResponseStatus();
		int NeedCloseConnect();
		int NeedParse();
		int WaitBody();
		void SetCloseConnection(int CloseConnect);
		std::map<std::string, std::string> GetHeaders();

		void ParseRequest(std::string line);
		void RequestLine(std::string line);
		void AddHeader(std::string line);
		std::string ReadRequest(int fd);
		void ReadBody(int fd);
};

std::ostream& operator << (std::ostream& cout, const std::map<std::string, std::string> c);

#endif
