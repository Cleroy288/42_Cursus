#include "../../parsing/server/server.hpp"
#include "../request/request.hpp"
#include "../../cgi/cgi.hpp"
#include "../request/reponse.hpp"

// function set to call basic functions of socket
void server::setupSocket(Socket &socket, int listenPort) {
    socket.create(); // Create the socket
    
    // Set socket options to reuse address and port
    int optval = 1;
    setsockopt(socket.getSocketFd(), SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    socket.bind(listenPort); // Bind it to the specified port
    socket.setNonBlocking(true);
    socket.listen(); // Set it to listen mode
    
    printString("Setting up a socket who listens on port : " + intToString(listenPort));
}


// function to create a socket that is going to listen on any incoming connection on the server
void server::clientConnectionSocket() {
	if (_listen.size() == 0) {
		printString("No socket to listen on");
		return;
	}
    if (_listen.empty()) { // if no ports are set up in the config file, then we set default port 80 to listen on
        try {
            Socket* sockeDefPort = new Socket();
            printString("No port to listen on found so default port 80 + index server will be set");
            _connectionSocket.push_back(sockeDefPort); // push socket pointer
            setupSocket(*_connectionSocket.back(), (80 + _index)); // setup to port 80 which is the default port
        } catch (const std::exception& e) {
            printErrs(e.what());
        }
    } else { // ports to listen on have been found
        for (size_t i = 0; i < _listen.size(); i++) {
            int port = std::atoi(_listen[i].c_str()); // convert port in int
            try {
                Socket* listenSocket = new Socket(); // dynamically create a new socket
                _connectionSocket.push_back(listenSocket); // push socket pointer
                setupSocket(*_connectionSocket.back(), port); // initialize socket on a given port
                printString("Socket who listens on port : " + intToString(port) + " and has fd : [" + intToString((_connectionSocket.back()->getSocketFd()))
				+ "] is set up and pushed to _connectionSocket");
            } catch (const std::exception &e) { // if error occurs then we show message error
                printErrs("Error in setup socket: " + std::string(e.what()));
            }
        }
    }
}

// print all the socket data of server, maybe later upgrade to print more info ?
void server::printAllSocketData() {
    printString("----------------");
    printString("printing data of all connection sockets");
    for (size_t i = 0; i < _connectionSocket.size(); i++) {
        if (_connectionSocket[i] != NULL) {  // Always good to check for null before dereferencing
            _connectionSocket[i]->printData(); // Use arrow operator to access members through pointers
        }
    }
    printString("----------------");
}


void server::setPollinOnEachCoSocket(std::vector<struct pollfd> &fds) {
    // POLLIN == constant from poll, used to show that a non-blocking reading process/event is available on a file descriptor
    // so basically POLLIN is used to show that data is ready to be read
    for (size_t i = 0; i < _connectionSocket.size(); i++) {
        if (_connectionSocket[i] != NULL) {  // Always good to check for null before dereferencing
            fds[i].fd = _connectionSocket[i]->getSocketFd();  // Use the arrow operator to access Socket members
            fds[i].events = POLLIN | POLLHUP; // POLLIN used to initialise each socket to listen for incoming connections and alert poll when a connection is coming
        }
    }
}

// set POLLIN val on each event fds , to be able to listen in incoming connections
void setPollinInFds(std::vector<struct pollfd> &fds) {
	for (size_t i = 0; i < fds.size(); i++) {
		fds[i].events = POLLIN | POLLHUP;
	}
}

// create a client , create a socket for him, gives him the socket and pushes the client to the server client list
int 	server::createSocketAndClient( sockaddr_in& client_addr, int& client_fd, int& client_id ) {
	
	if (client_fd < 0) {
		printString("BAD fd");
		return client_id - 1;
		//return -1;
	}

	Socket *ClientSocket = new Socket( client_fd );// create the new client socket connection
	Client* newClient = new Client(client_id, client_addr);// creation of the new client
	
	newClient->addSocket(ClientSocket);// add the socket to the client
	addClient(newClient);// add the client to the server client list
	return client_id;
}

int server::treatRequest( std::string header, size_t bytes_rec, int& client_fd ) {
	// std::string requestText(header, bytes_rec);
	(void)bytes_rec;
    request *req =  new request(header);  // Utilisation de la classe Request
	if (req->getMethod() == "") {
		delete(req);
		return 0;
	}

	/*************************** Begin Response ***************************/

	reponse rep(*req, *this, client_fd, bytes_rec);
	if (rep.getKillClient() == 1) {
		printString("Kill client");
		delete(req);
		return 1;
	}
	delete(req);

	/*************************** End Response ***************************/


	return 0;
}

// function called when a request has been send to the server
bool	server::startHandleRequet( int& client_id, int& client_fd ) {

	try {
		printString("(StartHandlRequest) :: Client id : "+ intToString(client_id));
		char buffer[2000000];
		size_t n_byte = 0;
		size_t bytes_rec = 0;
		std::string header;
		while ((bytes_rec = recv(client_fd, buffer, sizeof(buffer), 0)) > 0 && bytes_rec != std::string::npos) {
			buffer[bytes_rec] = '\0';
			if (bytes_rec == (size_t)-1 || bytes_rec == std::string::npos) {
				std::cerr << "Error while reading request !" << std::endl;
				return false;
			}
			n_byte += bytes_rec;
			header += buffer;
			if (header.find("\r\n\r\n") != std::string::npos) {
				break ;
			}
		}
		// if (bytes_rec == 0) {
		// 	// connection is lost
		// 	return false;
		// }
		if (treatRequest(header, n_byte, client_fd) == 1) {
			return false;
		}
		std::cerr << "Request treated" << std::endl;
		return true;
		// printString("***[ Starting to try to read request ]***");
		// 	char buffer[1024];
		// 	int bytes_rec = recv(client_fd, buffer, sizeof(buffer), 0);
		// 	printString("###    *** Bytes recieved => : " + intToString(bytes_rec));
		// 	if (bytes_rec > 0) {
		// 		printString("Client fd : " + intToString(client_fd) + " client id : " + intToString( client_id ));
		// 		printString("###    *** Bytes recieved => : " + intToString(bytes_rec));

		// 		treatRequest( buffer, bytes_rec, client_fd );// treat the incoming request
				
        //     	// std::string responseMsg = "HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nHello, world!";
        //     	// send(client_fd, responseMsg.c_str(), responseMsg.size(), 0);
                
		// 		return true;

		// 	} else if (bytes_rec == 0) {// connection is lost
		// 		//printString("Bytes read are == 0, client id [ " + intToString(client_id) + " ] has LOST CONNECTION");
		// 		return false;
		// 	} 
		// 	// treat the request and create reponse
		// 	else {
		// 		printErrs("Bytes recieved are ==> " + intToString(bytes_rec));
		// 		printErrs("recv error on client ID: " + intToString(client_id));
		// 		return false; // Signale une erreur
		// 		//break ;
		// 	}
	}
	catch(std::exception& e) {
		std::cerr << "Request not treated" << std::endl;
		printErrs(e.what());
		return false;
	}
	return true;
}


// set up the clientfd in à non blocking state and set to KEEP_ALIVE
void 	setupClientConnectionSocket( int& client_fd ) {

	try {
		// set socket KEEP_ALIVE , NON - BLOKING and re-usable
		// set socket non blocking
		int flags = fcntl(client_fd, F_SETFL, 0);
		flags |= O_NONBLOCK;
		fcntl(client_fd, F_SETFL, flags);
		// enable keep alive on the socket
		int optval = 1;
		socklen_t optlen = sizeof(optval);
		setsockopt(client_fd, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen);
	}
	catch(std::exception &e) {
		printErrs(e.what());
	}
}

// uses accept to accept incoming connection and send back the client_fd
int server::createClientfd(sockaddr_in& client_addr, int fd) {
    int i = 0;
    for (size_t j = 0; j < _connectionSocket.size(); j++) {
        if (_connectionSocket[j]->getSocketFd() == fd)
            i = j;
        else if (j == _connectionSocket.size())
            i = -1; 
    }
    
    if (i < 0 || static_cast<size_t>(i) >= _connectionSocket.size() || !_connectionSocket[i]) {
        printString("ERROR in [ createClientfd ] : Index out of range or null socket reference. i = [ " + intToString(i) + " ]");
        return -1;
    }

    socklen_t client_len = sizeof(client_addr);
    int client_fd = _connectionSocket[i]->accept(&client_addr, &client_len); // Accept incoming connection to get the client_fd 
    if (client_fd == -1) {
        perror("accept");
        return -1;
    }
    
    // Set socket options to reuse address and port
    int optval = 1;
	// function of socket, permits to set different params on a socket
    setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));// set REUSEADDR to set port imediately reusable

    return client_fd;
}


// supp the client and show à nice message in result.txt
void server::handleFailedRequest(int client_fd, std::vector<struct pollfd>& fds, size_t index) {
    printString("*** START HANDLE REQUEST HAS FAILED client_fd will be closed and erased from fds ***");
    if (index >= fds.size()) {
    	//fds.erase(fds.begin() + index);
		printString("ERROR IND HANDLEFAILEDREQUEST");
		return ;
	} 

	// set -1 on fd we are supposed to rip off
	for (size_t i = 0; i < fds.size(); i++) {
		if (fds[i].fd == client_fd)
			fds[i].fd = -1;
	}

	int fd = client_fd;
	for (size_t j = 0; j < _clients.size(); ++j) {
        if (_clients[j]->hasSocketFd(fd)) {// has the socket fd who disconnected
            printString("==> *** Client disconnected with ID: [ " + intToString(_clients[j]->getSessionId()) + " ] && socket FD : [ " + intToString(fd) + " ] *** ");
			_clients[j]->setRemove(-1);
			break;// break the spaghetti 
        }
    }
	printErrs("MARKED FD IS SET --> fds. Currentsize : " + intToString(fds.size()) + " Capacity : " + intToString(fds.capacity()) + " _client size is : " + intToString(_clients.size()) + " on server : " + intToString(_index));
}

// sets the new create client socket to fds to monitor hes requestes requests
void server::addNewClientToFds(int client_fd, std::vector<struct pollfd>& fds) {

	//for (size_t i = 0; i < fds.size(); i++) {
	//	if (fds[i].fd == client_fd) {
	//		printString("Client fd already in fd");
	//		return ;
	//	}
	//}
	
    fds.reserve(fds.size() + 1);// adds an extra place to fds
    struct pollfd clientFd = {};
    clientFd.fd = client_fd;
    clientFd.events = POLLIN | POLLHUP;
    fds.push_back(clientFd);// push the new kid in fds to monito he's following actions
    setPollinInFds(fds);
	std::cerr << "Added new fd to fds. Current size: " << fds.size() << ", Capacity: " << fds.capacity() << " _clients size : " << intToString(_clients.size()) + " on server : " + intToString(_index) <<std::endl;// print debug message & I like them
}

// shows a nice message and find the fd of the clients and removes him like a THUG
void server::processClientDisconnection(std::vector<struct pollfd>& fds, size_t index) {
	
    if (index >= fds.size()) {
    	//fds.erase(fds.begin() + index);
		printString("ERROR IND PROCESSCLIENTDISCONNECTION");
		return ;
	} 

    int fd = fds[index].fd;
    printString("*** SEEMS LIKE A CLIENT DISCONNECTED ***");
    for (size_t j = 0; j < _clients.size(); ++j) {
        if (_clients[j]->hasSocketFd(fd)) {// has the socket fd who disconnected
            printString("==> *** Client disconnected with ID: [ " + intToString(_clients[j]->getSessionId()) + " ] && socket FD : [ " + intToString(fd) + " ] *** ");
            removeClient(_clients[j]->getSessionId());// rmeove him like there is no tomorrow
			_clients[j]->setRemove(-1);
            break;// break the spaghetti 
        }
    }
    
	// set -1 on fd we are supposed to rip off
	for (size_t i = 0; i < fds.size(); i++) {
		if (fds[i].fd == fd)
			fds[i].fd = -1;
	}
	//fds.erase(fds.begin() + index);// erase him from fds cuz we finish business proprely here 
}

bool server::isConnectionSocket(int fd) {
    for (size_t i = 0; i < _connectionSocket.size(); i++) {
        if (_connectionSocket[i]->getSocketFd() == fd)
            return true; // is a connection socket
    }
    return false;
}


bool server::isClientSocket(int fd) {
    for (size_t i = 0; i < _clients.size(); i++) {
        if (_clients[i]->hasSocketFd(fd))
            return true;  // is a connection socket
    }
    return false;
}

bool server::isFdAlreadyMonitored( int client_fd) {
    if (isConnectionSocket(client_fd) == true)
		return false;
    else if (isClientSocket(client_fd) == true)
		return false; 
	return true;
}

int server::finClientIDWithFd( int fd ) {
	for (size_t i = 0; i < _clients.size(); i++) {
		if ( _clients[i]->hasSocketFd(fd) ) {
			return _clients[i]->getSessionId();
		}
	}
	printString("findClientIDWithFd no fd has been found -1 is return");
	return -1;
}

// function used to start a server
void server::startServer( std::vector<struct pollfd>& fds, int i ) {

	static int client_id = 0;
	//printString("clinets size before : " + intToString(_clients.size()));
	int fd = fds[i].fd;
	//printString("fds size before :" + intToString(fds.size()));

	printString("");
	try {
		//printString("Print all clients and client id");
		printString("client size : " + intToString(_clients.size()));
		//for (size_t i = 0; i < _clients.size(); i++) {
		//	printString("Client id : " + intToString(_clients[i]->getSessionId()) + " index i is : " +intToString(i));
		//}
		if ( isConnectionSocket( fd )) {//fds[i].fd ) ) { // is a connection socket so we can create a new client
			printString("### **** [" + intToString(fds[i].fd) + "] is a CONNEXION SOCKET **** ###");
			sockaddr_in client_addr;
        	int client_fd = createClientfd(client_addr, fd);// acept the incoming connection on socket and create fd 
			if (client_fd == -1) {// incase connection of client is lost
        	    processClientDisconnection(fds, i);// find client id , and fd and remove them from fds and _clients
				client_id--;
				return ;
        	}
        	client_id = createSocketAndClient(client_addr, client_fd, client_id);// create the client and adss it to the list of clients of server
        	setupClientConnectionSocket(client_fd);// set it socket in keep alive mode and non blocking , re - usable for next requests of client
			if (!startHandleRequet(client_id, client_fd)) {
            	handleFailedRequest(client_fd, fds, i);// handle in cas a request has failed
				client_id --;
				return ;
        	}
			addNewClientToFds(client_fd, fds);// else add the client back to fds to monitor for  incoming connections 
			client_id++;
			return ;
		} else {
			printString(" ####    IN else in server id : " + intToString(_index) + " #### ");
			//printString("### **** [" + intToString(fds[i].fd) + "] is a CLIENT CONNEXION **** ###");
			int client_fd = fds[i].fd;
			// find a way to get the right client id
			client_id = finClientIDWithFd( client_fd );
			if (client_id == -1 || client_fd == -1) {
				printString("Client id is -1");
				processClientDisconnection(fds, i);
				return ;
			}
			if (!startHandleRequet(client_id, client_fd)) {
            	handleFailedRequest(client_fd, fds, i);// handle in cas a request has failed
				client_id --;
				return ;
        	}
			return ;
		}
	}
	catch (std::exception& e) {
		setPollinInFds(fds);
	}
					
    printString("*** OUT ****");
	printString("");
}

// used to add a client to the client vector
void	server::addClient( Client *client ) {
	printString("Add client is called");
	if (client != NULL)
		_clients.push_back( client );// add client to _client list of server
	else
		printString("Error client val was NULL");
}

// used to remove a client 
void server::removeClient(int sessionId) {
    for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ) {
        if ((*it)->getSessionId() == sessionId) {  // session id found
            delete *it;  // delete the allocated Client object
            std::cerr << "Client with id [ " << intToString( sessionId ) << " ] removed" << std::endl;
            it = _clients.erase(it);  // erase the pointer from the vector
            return;
        } else {
            ++it;
        }
    }
    printString("removeClient called but client not found");
}

