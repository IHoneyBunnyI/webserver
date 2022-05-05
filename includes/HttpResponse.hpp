#ifndef HTPPRESPONSE
#define HTPPRESPONSE
#include "HttpRequest.hpp"
#include "ServerConfig.hpp"

class HttpResponse {
	private:
		HttpResponse();
		HttpResponse(const HttpResponse &r);
		HttpResponse& operator = (const HttpResponse& ref);

		std::string Method;
		std::string Path;
		std::string Version;
		std::map<std::string, std::string> Headers;
		std::string Body;
		int ResponseStatus;
		bool &CloseConnect;
		ServerConfig& Server;
		int fd;
	public:
		HttpResponse(HttpRequest &request, ServerConfig &server, int fd);
		~HttpResponse();
		void Response();
		void Get(Location &location);
		//void Post();
		//void Delete();
		void Error(int ResponseStatus);
		void SendDefaultError(int ResponseStatus);
		int GetResponseStatus();

		void SendHttp(std::string statusLine, std::string Headers, std::string path);

		void SendDefaultErrorPage(std::string statusLine, std::string Headers, std::string error_page);
};

std::string GenStatusLine(int ResponseStatus);
std::string GenHeaders(std::string path);
#endif
