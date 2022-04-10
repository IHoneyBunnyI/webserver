#include "HttpResponse.hpp"

HtppResponse::HtppResponse(HtppRequest request):
	Method(request.GetMethod()),
	Path(request.GetPath()),
	Version(request.GetVersion()),
	Headers(request.GetHeaders())
{}
