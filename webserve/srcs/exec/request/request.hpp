#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "../../../includes/principal.hpp"

class request {

	private:
		std::string 						_method;
		std::string 						_uri;
		std::string 						_httpVersion;
		std::string 						_body;
		std::string							_bodyForPost;
    	std::map<std::string, std::string>	_headers;
		std::string							_fullHeader;

	public:
		request( std::string& requestText );
		~request();
		void 	parseRequestLine( std::string& line );
		void 	parseHeader( std::string& line );

		std::string getMethod() { return _method; }
		std::string getUri() { return _uri; }
		std::string getBody() { return _body; }
		std::string getFullHeader() { return _fullHeader; }

		void	putInBody(std::string &body) { _body += body; }

};


#endif