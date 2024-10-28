#include "client.hpp"
#include "../../../includes/principal.hpp"

// constructor to make à défault client
Client::Client( int sessionId, sockaddr_in &addreInfo ) {
	
	_sessionId = sessionId;// set session id 
	_client_addr = addreInfo;// strcuture who has data of fd , ip adress and stuff 
    _remove = 0;// set remove to def val set -1 when you want it dead

	printString("Client default constructor called");
}

// used to add a socket to a client 
void Client::addSocket(Socket* socket) {
    printString("Number of socket client + " + intToString(_SocketClient.size()));
	if (socket == NULL) {
        printString("Error socket null tried ot be add at client");
        return ;
    }
    printString( "Socket ho listens on port : " + intToString(socket->getSocketFd()) + " is added to client id : " + intToString(_sessionId));
    _SocketClient.push_back( socket );  // Store pointer to socket
}


// used to remove a sokcet from the _SocketClient using an iterator
void Client::removeSocket(int socketFd) {
    std::vector<Socket*>::iterator it = _SocketClient.begin();  // use iterator to iterate through the container
    while (it != _SocketClient.end()) {
        if ((*it)->getSocketFd() == socketFd) {  // if value of index matches the socked fd to remove
            delete *it;  // remove socket
            it = _SocketClient.erase(it);  // remove socket from pointer
            printString("Socket removed from client");
            return;  // return 
        } else {
            ++it;  // incrementation 
        }
    }
    printString("remove socket called and socket was not found");
}

// function used to know is client has the fd in he's sockets
bool Client::hasSocketFd(int fd) {
    for (size_t i = 0; i < _SocketClient.size(); ++i) {
        if (_SocketClient[i]->getSocketFd() == fd) {
            return true;
        }
    }
    return false;
}


// Modification to handle dynamic memory in destructor of Client
Client::~Client() {
	printString("Client default destructor has been called");
    for (size_t i = 0; i < _SocketClient.size(); i++ ) {
        if ( _SocketClient[i] && _SocketClient[i] != NULL ) {
            printString("Socket with listening on port : " + intToString(_SocketClient[i]->getSocketFd()) + " has been deleted");
		    delete _SocketClient[i];  // Properly delete sockets to free resources
        }
    }
}