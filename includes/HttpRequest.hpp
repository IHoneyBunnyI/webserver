#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <iostream>
#include <map>

class HtppRequest {
public:
	HtppRequest(std::string request);
	~HtppRequest();
private:
	HtppRequest();
	HtppRequest(const HtppRequest& ref);
	HtppRequest& operator = (const HtppRequest& ref);

	std::string Method;
	std::string Path;
	std::string Version;
	std::map<std::string, std::string> Headers;
	//все хэдэры в реализации не нуждаются, only HTPP1.1
};

#endif
