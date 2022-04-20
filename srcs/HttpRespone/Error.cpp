#include "HttpResponse.hpp"

void HttpResponse::Error() {
	std::string file;
	for (unsigned int i = 0; i < this->Server.error_pages.size(); i++) {
		for (unsigned int j = 0; j < this->Server.error_pages[i].errors.size(); j++) {
			if (this->Server.error_pages[i].errors[j] == this->BadRequest) {
				file = this->Server.error_pages[i].error_page;
				this->CloseConnect = 1;
			}
		}
	}
	std::cout << "FILE:" << file <<  std::endl;
}
