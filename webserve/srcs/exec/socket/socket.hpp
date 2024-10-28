#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "../../../includes/principal.hpp"

// class used to create websockets 
class Socket {
	private:
		int 		_sockFd; // identifyer of the socket 
		sockaddr_in _address; // structure who is used to keep the IPV4 of the socket 

	public:
		Socket( );
		Socket( int fd );
		~Socket( );
		void 	create();
		void 	bind( const int port );
		void 	listen();
		int 	accept();
		int 	accept(sockaddr_in* clientAddr, socklen_t* addrLen);
		void 	setNonBlocking( const bool );
		int		getSocketFd();
		void 	printData();
};

#endif