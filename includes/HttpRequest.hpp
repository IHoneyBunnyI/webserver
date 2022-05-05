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
		bool CloseConnect;
		bool RequestLineExist;
		bool HeadersExist;
		int ResponseStatus;
		uint State;
		uint First;
	public:
		HttpRequest();
		~HttpRequest();

		std::string GetRequest();
		std::string GetMethod();
		std::string GetPath();
		std::string GetVersion();
		void UpdateFirst();
		bool GetHeadersExist();
		int GetResponseStatus();
		bool NeedCloseConnect();
		bool NeedParse();
		bool WaitBody();
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
