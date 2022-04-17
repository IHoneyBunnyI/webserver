#ifndef HTPPRESPONSE
#define HTPPRESPONSE
#include "HttpRequest.hpp"

class HtppResponse {
	public:
		HtppResponse(HttpRequest &request);
	private:
		std::string Method;
		std::string Path;
		std::string Version;
		std::map<std::string, std::string> Headers;
};

#endif
