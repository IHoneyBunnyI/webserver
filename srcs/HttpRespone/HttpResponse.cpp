#include <iostream>
#include "webserv.hpp"
#include "HttpResponse.hpp"

HtppResponse::HtppResponse(HtppRequest &request):
	Method(request.GetMethod()),
	Path(request.GetPath()),
	Version(request.GetVersion()),
	Headers(request.GetHeaders()) {
	std::cout << YELLOW << this->Method << WHITE << std::endl;
	std::cout << YELLOW << this->Path << WHITE << std::endl;
	std::cout << YELLOW << this->Version << WHITE << std::endl;
	}
