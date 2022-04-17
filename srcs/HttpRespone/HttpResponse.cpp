#include <iostream>
#include "webserv.hpp"
#include "HttpResponse.hpp"

HtppResponse::HtppResponse(HttpRequest &request):
	Method(request.GetMethod()),
	Path(request.GetPath()),
	Version(request.GetVersion()),
	Headers(request.GetHeaders()) {
	}
