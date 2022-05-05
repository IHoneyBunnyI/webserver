#include "HttpResponse.hpp"
#include <fstream>
#include <sys/stat.h>

void HttpResponse::Get(Location &location) {
	// создаем стрим пытаемся открыть и если директория пробуем открыыть index, иначе открываем файл и отправляем
	std::ifstream file;
	file.open(location.root + this->Path);
	if (file.is_open()) {
		//std::cout << "OPEN" << std::endl;
		struct stat buf;
		std::memset(&buf, 0, sizeof(buf));
		stat((location.root + this->Path).c_str(), &buf);
		if (S_ISDIR(buf.st_mode)) {
			//std::cout << "IS DIR" << std::endl;
			std::ifstream index;
			//тут надо найти существующий индекс и вернуть его 
			//std::string indexPath = findIndex(location.indexes);
			//index.open(location.root + this->Path + indexPath);
			//пробуем открыть index в этой dir
		} else {
			//std::cout << "IS NOT DIR" << std::endl;
			//пробуем открыть этот файл 
		}
	}
	else {
		//std::cout << "NOT OPEN" << std::endl;
		this->Error(404);
	}
}
