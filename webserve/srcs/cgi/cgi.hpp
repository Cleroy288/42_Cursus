#ifndef CGI_HPP
# define CGI_HPP

#include <map>
#include "../../includes/principal.hpp"

class reponse;

class Cgi {
	private:
		std::map <std::string, std::string>	_env;
		std::string 						_fullRequest;
		int									_client_fd;
		reponse&							_reponse;
		int									_contentLength;
		std::string							_userInput;

	public:
		Cgi( reponse& reponse );
		~Cgi();
		Cgi& operator=( const Cgi& other );

		std::string getUrl();
		std::string getValueInFullRequest( std::string search );
		std::string getUserInput();
		int			getContentLength();
	
		void setEnv( std::string pathInfo );
		void setContentLength();
		void setUserInput();

		std::map<std::string, std::string> getEnv( void );
		int	getClientFd();
		std::string getFullHeader();
		char** envToTab();

		class occurenceNotFound: public std::exception {
    		public:
				virtual const char* what() const throw() {
					return "Error: out of the array";
				}
		};
};

void executeCgi( reponse& reponse, std::string pathInfo );

#endif