#include <iostream>
#include "HttpRequest.h"



int main() {
	std::string httpRequestStr = "GET /wiki/http HTTP/1.1\n\
Host: ru.wikipedia.org\n\
User-Agent: Mozilla/5.0 (X11; U; Linux i686; ru; rv:1.9b5) Gecko/2008050509 Firefox/3.0b5\n\
Accept: text/html\n\
Connection: close";

	HttpRequest request(httpRequestStr);

	std::cout << request.getRequestType() << std::endl;
	std::cout << request.getRequestUrl() << std::endl << std::endl;

	std::vector<std::string> headers { std::move(request.getRequestHeaders()) };

	for (auto header = headers.begin(); header != headers.end(); header++) {
		std::cout << *header << ": " << request.getHeaderValue(*header) << std::endl;
	}


	return 0;
}