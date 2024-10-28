#include "socket.hpp"

// binds the socket to a specified port 
void Socket::bind( const int port ) {

	try {
		_address.sin_family = AF_INET; // configure the family adress to wich the socket belongs to a ipV4
		_address.sin_addr.s_addr = INADDR_ANY; // connect websocket to anny ip adress of the machine 
		_address.sin_port = htons(port); // htons convert port to network number usable by the machine 
		if (::bind(_sockFd, (struct sockaddr *)&_address, sizeof(_address )) != 0) {// binds the port & ip adress to socket 
			throw std::runtime_error("Could not create socket on port [ " + intToString(port) + " ]");
		}
	}
	catch( std::exception &e) {
		printErrs(e.what());
	}
}


// needs to create a socket who use tcp and ipv4
void Socket::create() { // function used to create à socket , this calls the défault socket constructor
	_sockFd = socket( AF_INET, SOCK_STREAM, 0 ); // AF_INET specifys that de IP adress will be ipv4, SOCK_STREAM specifies that connection will be TCP
	if ( _sockFd == -1 ) {
		throw std::runtime_error("Could not create socket");
	}
}

// set socket in listen mode and makes it wait for a connection 
void Socket::listen() {
	if (::listen(_sockFd, SOMAXCONN) != 0) { // set socket with _sockFd in listen mode, SOMAXCONN is used to set a maximum amount of of connexions depending on your OS
		throw std::runtime_error("Could not listen on socket");
	}
}

// accepts an incoming connection on socket 
int Socket::accept() {
	int client_sock = ::accept(_sockFd, NULL, NULL); // ecppets the first connection in buffer
	if (client_sock == -1) {// if val == -1 , return error 
		//printErrs("Could not accept client");
		//return -1;
		throw std::runtime_error("Could not accept client");
	}
	
	return client_sock;
}

// function used to accept incoming connection 
int Socket::accept(sockaddr_in* clientAddr, socklen_t* addrLen) {
    int clientSock = ::accept(_sockFd, (struct sockaddr*) clientAddr, addrLen);
    if (clientSock == -1) {
        //printErrs("Could not accept client");
		//return -1;
		throw std::runtime_error("Could not accept client");
    }
    return clientSock;
}

// function used to set a socket in non blockant (mode?)
void Socket::setNonBlocking( const bool b) {
	int opts;

	opts = fcntl( _sockFd, F_SETFL );// get the flags of the current socket 

	if (opts < 0) {
		return ;
	}
	if (b)// set on the non blockant flags, flag 0_NONBLOCK
		opts = ( opts | O_NONBLOCK );
	else// sets off the non blockant flags, with flag -0_NONBLOCK 
		opts = ( opts & -O_NONBLOCK );

	fcntl( _sockFd, F_SETFL, opts );// applies the new flags to the socket 
}

// default constructor for socket , it prepares the _address structure to have socket informations 
Socket::Socket( ) {

	printString("default constructor Socket called");

	// prepares the structure to be able to have the socket data 
	memset( &_address, 0, sizeof(_address));

}

// Constructor for a new socket from an existing file descriptor
Socket::Socket(int fd) : _sockFd(fd) {
	
	if (_sockFd == -1) {// error management
    	throw std::runtime_error("Invalid file descriptor supplied to Socket constructor");
    }

	printString("Socket created with existing file descriptor: " + intToString(fd));//nbr);
	// prepares the structure to be able to have the socket data 
	memset( &_address, 0, sizeof(_address));
	_address.sin_family = AF_INET; // IPv4 type of socket
	setNonBlocking(true);

}

void Socket::printData() {
	printString("sockfd : " + intToString(_sockFd));
}

// default destructor of socket  
Socket::~Socket() {
	printString("Default Socket destructor called, socket who listens on port : " + intToString(_sockFd) + " is destroyed");
	if (_sockFd != -1) {// close the socket if it has been opened (so the val is not -1)
		close(_sockFd);
	}
}

// function to send back sockFd
int Socket::getSocketFd() {
	return _sockFd;
}