#include "HttpResponse.hpp"
#include <sys/socket.h>
#include <fstream>

void HttpResponse::Error(int ResponseStatus) {
	std::string path_file;
	//закрываем соедениение и ищем файл из дефолтных
	this->CloseConnect = 1;
	for (uint i = 0; i < this->Server.error_pages.size(); i++) {
		for (uint j = 0; j < this->Server.error_pages[i].errors.size(); j++) {
			if (this->Server.error_pages[i].errors[j] == ResponseStatus) {
				path_file = this->Server.error_pages[i].error_page;
			}
		}
	}
	
	//если файла не нашлось отправляем стандартную ошибку
	std::ifstream file;
	if (path_file.empty()) {
		this->SendDefaultError(ResponseStatus);
		return;
	} else {
		file.open(path_file);
		//если  файл не открывается по каким либо причинам отправляем дефолт
		if (!file) {
			this->SendDefaultError(ResponseStatus);
			return;
		} else { // иначе закрываем зная, что он открывается и генерируем хэдеры
			file.close();
		}
	}
	
	std::string StatusLine = GenStatusLine(ResponseStatus);
	std::string Headers = GenHeaders(path_file);
	SendHttp(StatusLine, Headers, path_file);
}
