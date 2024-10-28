#ifndef NGINX_HPP
#define NGINX_HPP

#include "../../../includes/principal.hpp"
#include "../server/server.hpp"

class nginx {
	private:
		// stock here each server data
		const std::string 			_pathToFile;
		
		// here we are going to stock every instance of server we find in the nginx file
		std::vector<server *> 		_servers;

		// here we stcok the full content of the nginx file , so that we can acces it later if we want to
		std::vector<std::string> 	_nginxContent;

		// number of servers 
		size_t 		_nbrOfServer;

		// 
		std::vector<struct pollfd> _fds;

		bool 	isGeneralServerParameter(const std::string& word, const std::vector<std::string>& possibleParams);

	public:
		nginx( const std::string &pathToFile );
		~nginx( );// destructor

		bool 	findAndStockServerData ();
		bool 	startAllServers();
		bool 	processFdEvent( size_t index );
		void	initConnectionSockets();
		void 	handlePollErrors(int ret);
		void 	setAllFdsToPollIn();
		void 	removeAndPrint();
		// parsing functions 
		bool 	isFileContentValid();
		bool 	isThereOnlyServParts( std::vector<std::string> _tokenizedNginxContent );
		bool 	verifyGenParamInServ( std::vector<std::string> _tokenizedNginxContent );
		bool 	verifyParam(const std::string& nameParam, const std::vector<std::string>& params);
		bool 	processServerParameters(std::string& word, bool inServ, bool inLoc, bool& setParam, std::string& currentParamName, std::vector<std::string>& currentParams, const std::vector<std::string>& possibleParam);
		bool 	handleBlockState(const std::string& word, bool& inServ, bool& inLoc);
		bool 	verifyLocationParams( std::vector<std::string> _tokenizedNgixContent );
		bool 	verifyImportantServerVal();


		bool	setToBeRemovedValOnClientFd(int fd) {
			for (size_t i = 0; i < _servers.size(); i++) {
				if (_servers[i]->setToRemoveClientWithFd(fd))
					return true;
			}
			return false;
		}


};

#endif