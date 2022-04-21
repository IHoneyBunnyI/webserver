#ifndef HTPPRESPONSE
#define HTPPRESPONSE
#include "HttpRequest.hpp"
#include "ServerConfig.hpp"

class HttpResponse {
	public:
		HttpResponse(HttpRequest &request, ServerConfig &server, int fd);
		~HttpResponse();
		void Response();
		void Get();
		//void Post();
		//void Delete();
		void Error();
		void SendDefaultError(int fd, int ResponseStatus);


		void SendStatusLine(std::string statusLine);
		void SendHeaders(std::string headers);
		void SendDefaultErrorPage(std::string error_page);
		void SendPage(int fd, std::string path);
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
		int &CloseConnect;
		ServerConfig& Server;
		int fd;
};

std::string GenStatusLine(int ResponseStatus);
#endif
