#ifndef HTPPRESPONSE
#define HTPPRESPONSE
#include "HttpRequest.hpp"
#include "ServerConfig.hpp"

class HttpResponse {
	public:
		HttpResponse(HttpRequest &request, ServerConfig &server, int fd);
		~HttpResponse();
		void Send();
		void Get();
		//void Post();
		//void Delete();
		void Error();
		void SendDefaultError(int fd, int ResponseStatus);
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

#endif
