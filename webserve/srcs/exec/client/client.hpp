#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../socket/socket.hpp"
#include "../../../includes/principal.hpp"

// this class will be used to identify a cleint on the server and is IP adress and the sources port
class Client {

	private:
		sockaddr_in 		_client_addr; // structure who keep data of client connection like, ip adress and fd and other stuff i suppose
		int 				_sessionId; // unique session id for user 
		std::vector<Socket*> _SocketClient; // the number of his websocket connections
		int 				_remove ;


	public:
		//Client( std::string &ipAdress, int SessionId );// défault constructor 
		Client( int sessionId, sockaddr_in &addreInfo );
		~Client();

		//void addSocket( Socket &socket );// adds a socket to to client 
		void addSocket(Socket* socket);

		void removeSocket( int sockFd );// willbe used to delete a socket i guess ... idk if its usefull anyway , probably not, or probably yes

		int getSessionId() { return _sessionId; } // will use to get session id to identify client
		std::string getIpaddress() {
			char ipStr[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &_client_addr.sin_addr, ipStr, sizeof(ipStr));
			return std::string(ipStr);
		}// will use to send back ip adress , i odnt already know why but can be usefull is guess ... 

    	int getPort() const { // Method to extract port from sockaddr_in
    	    return ntohs(_client_addr.sin_port);
    	}

		bool hasSocketFd(int fd); // send back true or false

		void setSessionId(int id) {_sessionId = id; }
		void setRemove(int val) {_remove = val;}
		int getRemoveVal() {return _remove;}

		void printAllSocketsFd() {
			for (size_t i = 0; i < _SocketClient.size(); i++) {
				printString("Socked in client id :  " + intToString(_sessionId) + " sock fd : " + intToString(_SocketClient[i]->getSocketFd()));
			}
		}

};

#endif