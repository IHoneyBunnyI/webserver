#include <iostream>
#include "webserv.hpp"
#include "HttpResponse.hpp"

HttpResponse::HttpResponse(HttpRequest &request, ServerConfig &server, int fd):
	Method(request.Method),
	Path(request.Path),
	Version(request.Version),
	Headers(request.Headers),
	Body(request.Body),
	BadRequest(request.BadRequest),
	CloseConnect(request.CloseConnect),
	Server(server),
	fd(fd) {
}

HttpResponse::~HttpResponse(){};

HttpResponse::HttpResponse():
	Method(),
	Path(),
	Version(),
	Headers(),
	Body(),
	BadRequest(),
	CloseConnect(*(new(int))),
	Server(*(new(ServerConfig)))
	{}

HttpResponse::HttpResponse(const HttpResponse &r):
	Method(r.Method),
	Path(r.Path),
	Version(r.Version),
	Headers(r.Headers),
	Body(r.Body),
	BadRequest(r.BadRequest),
	CloseConnect(r.CloseConnect),
	Server(*(new(ServerConfig))) {

}

HttpResponse& HttpResponse::operator = (const HttpResponse& ref) {
	if (&ref != this) {
		this->Method = ref.Method;
		this->Path = ref.Path;
		this->Version = ref.Version;
		this->Headers = ref.Headers;
		this->CloseConnect = ref.CloseConnect;
		this->BadRequest = ref.BadRequest;
		this->CloseConnect = ref.CloseConnect; //лажа
		this->Server = ref.Server;
	}
	return *this;

}
