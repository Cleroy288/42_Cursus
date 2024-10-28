#ifndef SERVER_HPP
#define SERVER_HPP

#include "../../../includes/principal.hpp"
#include "../../exec/client/client.hpp"
#include "../../cgi/cgi.hpp"
//#include "../nginx/nginx.hpp"

// TODO 
/**
 * 
 * 
 * vérifier que le premier char des /location sois un / 
*/

class server {

	private:
		std::vector<std::string> 	_listen;// port on wich we are going to listen 
		std::vector<std::string> 	_serverName;
		std::string 				_host;
		std::string 				_root;
		std::string 				_maxRequestBody;// client_max_body_size
		std::string 				_autoIndex;// on or of or empty
		std::string 				_cgi_timeout;// cgi timeout

		// index files
		std::vector<std::string> _indexFiles;

		// methodes GET DELETE POST ETC ...
		std::vector<std::string> _methodes;

		// index , to easely identify the serve rindex inf nginx file
		size_t 		_index;

		// used to stock the error codes and the way to the file
		std::vector<errorAndPages> _errorCodeAndPages;

		// full content of server part who is displayed
		std::vector<std::string> _content;

		// LOCATION , every node of location data has the data of one " location " part of nginx file
		// and a structure of locationData 
		std::vector<locationData> _locationData;

		// container of the clients who are connected to the server
		std::vector<Client *> _clients;


		// CGI PART 
		// --> CGI ROUTES 
		// --> right acces 
		// --> use fastcgi example , so we need to change de current implémentation we have for CGI ==> 
		/*
		
			location /cgi-bin/ {
				fastcgi_pass unix:/path/to/your/cgi-handler.sock;  // Le socket où votre gestionnaire CGI écoute
				include fastcgi_params;  // Paramètres génériques FastCGI
				fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
			}

		*/


	public:
		// container of the socket who are used to listen for incoming clients on server
		std::vector<Socket *>	_connectionSocket;
		// constructor who get a param with all the data of a server 
		server( const std::vector<std::string> &serverInfo, size_t serverIndex ) ;

		// default destructor
		~server();

		// get number of port on to wich to listen 
		size_t 	getnbrOfListen() { return _listen.size(); }

		// find _listen and _index and _serverName
		void 	putInWord( std::string word );
	
		// set _errorCodeAndPAges
		void 	findErrorPageAndCodes();
	
		// set : _listen, _host, _root, _maxRequestBody
		void	findData( const std::string &nameData );

		// set the _locationData 
		void	setLocation();

		/**   FUNCTIONS USED TO TREAT CLIENT IN SERVER   **/
		// used to add a client to the client vector
		void	addClient( Client *client );
		// used to remove a client 
		void	removeClient( int sessionId );

		/**    FUNCTIONS USED TO START SERVER 	**/ // USED in serverExec.cpp
		//void 	startServer( std::vector<struct pollfd> fds );
		//void	startServer();// initial function who calls all the beneeth functions to start a server
		//void 	startServer( struct pollfd fds );
		void 	startServer( std::vector<struct pollfd>& fds, int i );
		int 	createClientfd( sockaddr_in& client_addr, int fd );
		//void 	processClientDisconnection(std::vector<struct pollfd>& fds, int fd);
		void processClientDisconnection(std::vector<struct pollfd>& fds, size_t index);
			//void 	initListeningSocket();// initialize listening socket on _listen ports of server and set _fds val
			void 	setPollinOnEachCoSocket(std::vector<struct pollfd> &fds);// set POLLIN state on each _connectionSocket
			void 	setupSocket( Socket &socket, int listenPort );// function to setup a basic socket 
			void 	clientConnectionSocket( );// function to set up listen socket to wait for client conection 
			int 	createSocketAndClient( sockaddr_in& client_addr, int& client_fd, int& client_id );
			bool	startHandleRequet( int& client_id, int& client_fd );// uses recv to get request from incoming client and treat it
			int 	treatRequest( std::string header, size_t bytes_rec, int& client_fd );// function used to treat à received request
			// int 	createClientfd( sockaddr_in& client_addr, int i );// function used to accept incming connection from à connection socket and get client_fd
			void 	handleFailedRequest(int client_fd, std::vector<struct pollfd>& fds, size_t index);
			void 	addNewClientToFds(int client_fd, std::vector<struct pollfd>& fds);
			//void 	processClientDisconnection(std::vector<struct pollfd>& fds, size_t index);
			//bool 	isFdAlreadyMonitored( const std::vector<struct pollfd>& fds, int& client_fd);
			bool 	isFdAlreadyMonitored( int client_fd);
			bool 	isClientSocket( int fd );
			bool 	isConnectionSocket( int fd );
			int 	finClientIDWithFd( int fd );
			/**    FUNCTIONS USED TO START SERVER 	**/ // USED in serverExec.cpp
		// print the fd data of each _connectionSocket
		void 	printAllSocketData();

		// **** GETTERS **** // 
		// return "" incase nothing 
		std::string getErrorAndPages( int errorVal ); // get Error page in general part of server based of error code
		// std::string getErrorAndPages( int& errorVal );
		std::string getErrorAndPages( int errorVal, std::string locationName );// get error page based on error cad and location 
		// std::string getErrorAndPages( int& errorVal, std::string& locationName );
		std::string getNameOfLocationBAsedOnURL ( std::string& URL );
		std::string getCgiTimeOut() { return _cgi_timeout; }
		
		bool 		isAutoIndexOnInLoc( std::string locationName );
		bool 		isAutoIndexOnInGen(  );
		bool 		getAllowedMethod( std::string method, std::string location );
		std::string getRootInLoc( std::string location );
		std::string getRoot();
		std::string getAutoIndexGenVal();
		long getMaxRequestBody() { return std::atoi(_maxRequestBody.c_str()); }// getter max request body 
		long getCgi_timeout() { return std::atoi(_cgi_timeout.c_str()); }// getter cgi timeout

		std::vector<std::string> 	getIndexOfLocation(std::string locationName);
		std::vector<std::string> 	getListen() { return _listen; }
		std::string 				getHost() { return _host; }
		size_t 						getListenSize() { return _listen.size(); }
		size_t 						getServerIndex() { return _index; }
		size_t 						getClientSize() { return _clients.size(); }
		size_t 						getServerNameSize() { return _serverName.size(); }
		size_t 						getId(); // sent back server id / index
		std::string 				getRedirrectLocation(std::string location);

		void printClientWithRemoveVal() {
			for (size_t i = 0; i < _clients.size(); i++) {
				if (_clients[i]->getRemoveVal() == -1) {
					printString("Client with id : " + intToString(_clients[i]->getSessionId()) + " printing has socket data ==> ");
					_clients[i]->printAllSocketsFd() ;
					printString("------");
				}
			}
		}

		void removeClientWithRemoveVald() {
			std::cerr << "******************* ( in removeClientWithRemoveVald ) *******************" << std::endl;
			// Itérer sur la liste de clients en utilisant un itérateur
			for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ) {
				std::cerr << "1" << std::endl;
				//printString("Client with ID: " + intToString((*it)->getSessionId()) + " remove val is : " + intToString((*it)->getRemoveVal()) + " and ip is : " + (*it)->getIpaddress());
				// Vérifier si le client actuel doit être supprimé
				if ( (*it)->getRemoveVal() == -1 ) {//||  std::stoi((*it)->getIpaddress()) < 0) {
					std::cerr << "******************* REMOVING CLIENTS 2 *******************" << std::endl;
					printString("Client with ID: " + intToString((*it)->getSessionId()) + " marked for removal.");
					// Libérer la mémoire allouée pour le client
					delete *it;
					// Effacer l'élément de la liste et obtenir le nouvel itérateur
					it = _clients.erase(it);
				} else {
					// Avancer l'itérateur si le client n'est pas à supprimer
					++it;
				}
			}
		}

		void printClientSize() { printString("Client size in SERVER ID [" + intToString(_index) +"] is : " + intToString(_clients.size())); }

bool setToRemoveClientWithFd(int fd) {
	for (size_t i = 0; i < _clients.size(); i++) {
		if (_clients[i]->hasSocketFd(fd)) {
			_clients[i]->setRemove(-1);
			return true;
		}
	}
	return false;
}

		
};



#endif