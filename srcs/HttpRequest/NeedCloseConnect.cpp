#include "HttpRequest.hpp"

int HttpRequest::NeedCloseConnect() {
	if (this->CloseConnect == 1) {
		this->CloseConnect = 0;
		return 1;
	}
	return 0;
}
