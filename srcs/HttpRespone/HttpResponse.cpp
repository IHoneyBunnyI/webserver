#include <iostream>
#include "webserv.hpp"
#include "HttpResponse.hpp"

HtppResponse::HtppResponse(HtppRequest &request):
	Method(request.GetMethod()),
	Path(request.GetPath()),
	Version(request.GetVersion()),
	Headers(request.GetHeaders()) {
	std::cout << Method << std::endl;
	std::cout << Path << std::endl;
	std::cout << Version << std::endl;
	}
