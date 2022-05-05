#include "HttpRequest.hpp"

bool HttpRequest::NeedCloseConnect() {
	if (this->CloseConnect == true) {
		this->CloseConnect = false;
		return true;
	}
	return false;
}
