#include <algorithm>
#include "httpRequest.h"



/////////////////
// Private members
void HttpRequest::parseHeaders(const std::string& httpRequestStr) {
	// temporary string, to store row
	std::string row;
	// Initializing currentPos with index of beginning of 2nd row
	size_t currentPos{ httpRequestStr.find_first_of('\n', 0) + 1 };
	size_t nextPos{ 0 };

	// parsing rows with headers
	bool breakFlag{ true };
	while (breakFlag) {
		nextPos = httpRequestStr.find_first_of('\n', currentPos);

		if (nextPos == std::string::npos) {
			nextPos = httpRequestStr.length() - currentPos;
			breakFlag = false;
		}

		row = httpRequestStr.substr(currentPos, nextPos - currentPos);

		// Parsing row / filling headersMap
		{
			size_t colonPos{ row.find_first_of(':') };

			// if all headers where processed (empty row), stop parsing
			if (colonPos == std::string::npos) break;


			// Transform header name to Lowercase in a temporary string
			std::transform(row.begin(), row.begin() + colonPos, row.begin(),
				[](unsigned char c) { return std::tolower(c); });

			// +2 to get rid of space
			headersMap[row.substr(0, colonPos)] =
				row.substr(colonPos + 2, httpRequestStr.length() - colonPos);
		}

		currentPos = nextPos + 1;
	}
}

void HttpRequest::parseStartingLine(const std::string& httpRequestStr) {
	// setting currentPos to the start of the URI
	size_t currentPos{ httpRequestStr.find_first_of(' ') + 1 };

	// Note:
	// I assume, that request type in the given string will always be valid,
	// and there won't be any spaces at the beginning of the row
	switch (httpRequestStr[0] + httpRequestStr[1]) {
	case 140:
		requestType = HttpRequestType::GET;
		break;
	case 159:
		requestType = HttpRequestType::POST;
		break;
	case 146:
		requestType = HttpRequestType::CONNECT;
		break;
	case 165:
		requestType = HttpRequestType::PUT;
		break;
	case 141:
		requestType = HttpRequestType::HEAD;
		break;
	}


	// building URL
	requestUrl = "http://"
		+ headersMap["host"]
		+ httpRequestStr.substr(currentPos,
			httpRequestStr.find_first_of(' ', currentPos + 1) - currentPos);
}


/////////////////
// Public members
HttpRequest::HttpRequest(const std::string& httpRequest) {
	// Headers must be parsed before Starting line
	// to build requestUrl with value of "Host" header
	parseHeaders(httpRequest);

	parseStartingLine(httpRequest);
}

const std::string HttpRequest::getRequestUrl() {
	return requestUrl;
}

const HttpRequestType HttpRequest::getRequestType() {
	return requestType;
}

// Get Header's value by Header name
const std::string HttpRequest::getHeaderValue(std::string headerName) {
	std::transform(headerName.begin(), headerName.end(), headerName.begin(),
		[](unsigned char c) { return std::tolower(c); });

	return headersMap[headerName];
}

// get vector of headers
std::vector<std::string> HttpRequest::getRequestHeaders() {
	std::vector<std::string> headersVect;

	for (auto pair : headersMap) {
		headersVect.push_back(pair.first);
	}

	return headersVect;
}