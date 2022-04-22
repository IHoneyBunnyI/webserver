#include "HttpResponse.hpp"
#include "Parser.hpp"
#include <sys/socket.h>

std::string setResponseStatus(int ResponseStatus) {
	std::string statusLine;
	if (ResponseStatus == 200) {
		statusLine += "OK\n";
	} else if (ResponseStatus == 400) {
		statusLine += "Bad Request\n";
	} else if (ResponseStatus == 404) {
		statusLine += "Not Found\n";
	} else if (ResponseStatus == 405) {
		statusLine = "Method Not Allowed\n";
	} else if (ResponseStatus == 413) {
		statusLine = "Payload Too Large\n";
	} else if (ResponseStatus == 505) {
		statusLine = "HTTP Version Not Supported\n";
	}
	return statusLine;
}

std::string GenStatusLine(int ResponseStatus) {
	std::string statusLine;
	statusLine += "HTTP/1.1 ";
	statusLine += std::to_string(ResponseStatus) + " ";
	statusLine += setResponseStatus(ResponseStatus);
	return statusLine;
}

std::string pageWithError(std::string error) {
	std::string error_html = "\
<html>\n\
<head><title>***</title></head>\n\
<body>\n\
<center><h1>***</h1></center>\n\
<hr><center>Webserver</center>\n\
</body>\n\
</html>\n";
	Parser::replace_all(error_html, "***", error);
	return error_html;
}

std::string defaultPage(int ResponseStatus) {
	std::string error_html;
	if (ResponseStatus == 400) {
		error_html = pageWithError("400 Bad Request");
	} else if (ResponseStatus == 404) {
		error_html = pageWithError("404 Not Found");
	} else if (ResponseStatus == 405) {
		error_html = pageWithError("405 Method Not Allowed");
	} else if (ResponseStatus == 413) {
		error_html = pageWithError("413 Payload Too Large");
	} else if (ResponseStatus == 505) {
		error_html = pageWithError("505 HTTP Version Not Supported");
	}
	return error_html;
}

std::string GenDefaultHeaders(std::string error_page) {
	std::string Headers;
	Headers += "Server: webserver\n";
	Headers += "Content-Type: text/html\n";
	Headers += "Content-Length: " + std::to_string(error_page.length()) + "\n";
	Headers += "Connection: close\n\n";
	return Headers;
}

void HttpResponse::SendDefaultError(int ResponseStatus) {
	std::string statusLine = GenStatusLine(ResponseStatus);
	std::string error_page = defaultPage(ResponseStatus);
	std::string Headers = GenDefaultHeaders(error_page);
	SendStatusLine(statusLine);
	SendHeaders(Headers);
	SendDefaultErrorPage(error_page);
}
