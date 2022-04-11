#include "HttpRequest.hpp"

int HtppRequest::NeedCloseConnect() {
	if (this->close_connect == 1) {
		this->close_connect = 0;
		return 1;
	}
	return 0;
}
