#ifndef HTTP_REQUEST_HEADER
#define HTTP_REQUEST_HEADER

#include <string>
#include <unordered_map>



enum HttpRequestType {
	GET,	// 71 + 69	140
	POST,	// 80 + 79	159
	CONNECT,// 67 + 79	146
	PUT,	// 80 + 85	165
	HEAD	// 72 + 69	141
};


class HttpRequest {
private:
	std::string requestUrl;

	HttpRequestType requestType;

	std::unordered_map<std::string, std::string> headersMap;


	void parseHeaders(const std::string& httpRequestStr);

	void parseStartingLine(const std::string& httpRequestStr);

public:
	HttpRequest(const std::string& httpRequest);

	const std::string getRequestUrl();

	const HttpRequestType getRequestType();

	// Get Header's value by Header name
	const std::string getHeaderValue(std::string headerName);

	// get vector of headers
	std::vector<std::string> getRequestHeaders();

};

#endif