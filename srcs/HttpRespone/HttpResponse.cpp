#include <iostream>
#include "HttpResponse.hpp"

HtppResponse::HtppResponse(HtppRequest &request):
	Method(request.GetMethod()),
	Path(request.GetPath()),
	Version(request.GetVersion()),
	Headers(request.GetHeaders()) {
	//std::cout << this->Method << std::endl;
	//std::cout << this->Path << std::endl;
	//std::cout << this->Version << std::endl;
	}
