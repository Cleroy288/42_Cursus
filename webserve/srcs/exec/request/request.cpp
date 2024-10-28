#include "request.hpp"

request::request(std::string& requestText) {
    _fullHeader = requestText;
    std::string line;
    std::istringstream requestStream(requestText);
    std::getline(requestStream, line);
    parseRequestLine(line);
    while (std::getline(requestStream, line) && line != "\r") {
        parseHeader(line);
    }
    std::getline(requestStream, _body, '\0');
	// if (_method == "") {
	// 	_method = "GET";
	// 	_uri = "/vide";
	// 	_httpVersion = "HTTP/1.1";
	// 	std::cerr << "===============================================" << std::endl;
	// 	std::cerr << requestText << std::endl;
	// 	std::cerr << "===============================================" << std::endl;
	// }
}

request::~request() {}

void request::parseRequestLine(std::string& line) {
    std::istringstream requestLine(line);
    requestLine >> _method;
    requestLine >> _uri;
    requestLine >> _httpVersion;
}

void request::parseHeader(std::string& line) {
    std::string key;
    std::string value;
    std::istringstream headerLine(line);
    std::getline(headerLine, key, ':');
    std::getline(headerLine, value);
    _headers[key] = value;
}