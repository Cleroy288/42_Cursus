#include "nginx.hpp"

// destructor 
nginx::~nginx( ) {
	for (size_t i = 0; i < _servers.size(); i++) {
		std::string nbr = intToString(_servers[i]->getId());
		printString("Deleting server with server id : " +  nbr);
		delete _servers[i];
	}
}


// function to get the info of nginx file and display it in server class properly
bool nginx::findAndStockServerData() {
	
	int		braces = 0;
	int		serverIndex = 0;
	bool	serverFound = false;
	std::vector<std::string> tmpContainer;

	try {
		for (size_t index = 0; index < this->_nginxContent.size(); index++) {
		
			std::istringstream 	iss(this->_nginxContent[index]);
			std::string 		token;

			while (iss >> token) {

				if (token == "server") {
					// if else to make sure serverfound is always to the right value
					if (serverFound == false)
						serverFound = true;		
					else if (serverFound == false)
						serverFound = true;		
					
					if (braces != 0) {// error mangament of an extra server token 
						tmpContainer.clear();// clear if error happend
						throw std::runtime_error("an error has been found in the nginx file");
					}
				}
				// count braces to have à right file, always pair number of braces
				if (token == "{")
					braces ++;
				else if (token == "}")
					braces --;

				// Push to tmpContainer if we are in server {...} and or at the end of file
				if (serverFound == true) {
					if (braces != 0)// push if we are in server {...}
						tmpContainer.push_back(token);
					else if (braces == 0 && token == "}") // push if we are at end of file / last "}"
						tmpContainer.push_back(token);
					
				}
				// if at end of container we push the data to server
				if (serverFound == true && braces == 0 && tmpContainer.size() != 0) {
					try {
						server *newServ = new server(tmpContainer, serverIndex);
						// here we add to server 
						this->_servers.push_back( newServ );//server( tmpContainer, serverIndex ));
						serverIndex++;
						tmpContainer.clear();
					} catch (std::exception& e) {
						//throw std::runtime_error("error in creation of new server");
						return false;
					}
				}
			}
		}
		this->_nbrOfServer = serverIndex;// set number of server
		return true;
	}
	catch (std::exception &e) {
		printErrs(e.what());
		return false;
	}
}

nginx::nginx( const std::string &pathToFile ) : _pathToFile( pathToFile ) {

	try {
		// opening configuration file 
		std::ifstream 	file(pathToFile.c_str());
		// line we are going to read from it
		std::string		line;
		// open file 
		if (!file.is_open()) {
			throw std::runtime_error("Failed to openfile : " + pathToFile);
		}
		//extract content of file and set it in _nginxContent
		while (std::getline(file, line)) {
			// we do not keep the emppty lines, when a line is empty we skip
			if (!line.empty()) {
				if (!isValidLineFormat(line)) {// verify if each line starts with letters and ends with '{' or '}' or ';'
					printErrs("Line format error : [" + line +"]");
					file.close();
					throw std::runtime_error("Error in nginx file");
				}
				this->_nginxContent.push_back(line);
			}
		}
		// close file when done 
		file.close();
		// see if conent of nginx file is ok
		if (!isFileContentValid()) {
			throw std::runtime_error("Error in nginx file");
		}

		// print content for debug
		//printString("now lets print the content of _ngincontent ==> ");
		//for (size_t i = 0; i < this->_nginxContent.size(); i++)
		//	printString(this->_nginxContent[i]);

		// after we have the data we treat it
		if (!findAndStockServerData())
			throw ("Error in nginx file");

	}
	catch(std::exception& e) {
		throw std::runtime_error("error in nginx file");
	}
}

void	nginx::initConnectionSockets() {
	printString("");
	size_t conSock = 0;
	for (size_t i = 0; i < _servers.size(); i++) {
		conSock += _servers[i]->getnbrOfListen();
	}
	_fds.resize(conSock);
	printString("size of _fds.size() : " + intToString(_fds.size()));
	size_t fdIndex = 0;
	for (size_t i = 0; i < _servers.size(); i++) {
	    _servers[i]->clientConnectionSocket();
	    for (size_t j = 0; j < _servers[i]->getnbrOfListen(); j++) {
	        _fds[fdIndex].fd = _servers[i]->_connectionSocket[j]->getSocketFd();
	        _fds[fdIndex].events = POLLIN | POLLHUP;
	        printString("fds set fd is : " + intToString(_fds[fdIndex].fd));
	        fdIndex++;
	    }
	}
	printString("fds val verification ");
	for (size_t i = 0; i < _fds.size(); i++) {
	    printString("index : " + intToString(i) + " fd is : " + intToString(_fds[i].fd));
	}
	printString("****** ---- *******");
	for (size_t i = 0; i < _fds.size(); i++) {
		
		for (size_t j = 0; j < _servers.size(); j++) {
			for (size_t k = 0; k < _servers[j]->_connectionSocket.size(); k++) {
				if (_servers[j]->_connectionSocket[k]->getSocketFd() == _fds[i].fd) {
					printString("fds index : " + intToString(i) + " fd is : " + intToString(_fds[i].fd) +
					" has same fd as _connection socket " + intToString(k) + " from server "+ intToString(j) );
				}
			}
		}
	}
}


struct IsFdMarkedForRemoval {
    bool operator()(const pollfd& fd) const {
        return fd.fd == -1;
    }
};

void nginx::removeAndPrint() {

	printString("REMOVE AND PRINT FUNCTION");
	std::cerr << "servers size : " << _servers.size() << std::endl;
    for (size_t i = 0; i < _servers.size(); i++) {
        _servers[i]->removeClientWithRemoveVald();
	}
	// Suppression des fds marqués dans la structure globale _fds
    _fds.erase(std::remove_if(_fds.begin(), _fds.end(), IsFdMarkedForRemoval()), _fds.end());

}

bool checkForDuplicatePorts( std::vector<server*> servers) {
    std::vector<std::string> allPorts;

    // Collecter tous les ports de tous les serveurs
    for (size_t i = 0; i < servers.size(); ++i) {
        std::vector<std::string> listenPorts = servers[i]->getListen();
        for (size_t j = 0; j < listenPorts.size(); ++j) {
            if (std::find(allPorts.begin(), allPorts.end(), listenPorts[j]) != allPorts.end()) {
                std::cerr << "Duplicate port found: " << listenPorts[j] << std::endl;
                return false; // Un doublon a été trouvé
            }
            allPorts.push_back(listenPorts[j]);
        }
    }

    std::cout << "No duplicate ports found." << std::endl;
    return true; // Aucun doublon n'a été trouvé
}

bool nginx::verifyImportantServerVal() {
    for (size_t i = 0; i < _servers.size(); i++) {
        server* server = _servers[i];

        // Vérification du root
        std::string root = server->getRoot();
        if (root.empty() || root == "def") {
            printString("ERROR :: Server index : [" + intToString(server->getId()) + "] has no root.");
            return false;
        }

        // Vérification des ports d'écoute
        if (server->getListenSize() == 0) {
            printString("ERROR :: Server index : [" + intToString(server->getId()) + "] has no ports to listen on.");
            return false;
        }

        // Vérification de l'hôte
        std::string host = server->getHost();
        if (host == "def" || host.empty()) {
            printString("ERROR :: Server index : [" + intToString(server->getId()) + "] has no host.");
            return false;
        }

        // Vérification du nom du serveur
        if (server->getServerNameSize() == 0) {
            printString("ERROR :: Server index : [" + intToString(server->getId()) + "] has no serverName.");
            return false;
        }
    }

    // Vérification des doublons de ports si nécessaire
    if (!checkForDuplicatePorts(_servers)) {
        return false;
    }

    return true; // Toutes les vérifications sont passées
}


volatile sig_atomic_t stopRequested = 0;// volatile == val can change anny moment , sig_atomic_t == can be read and written to completely at same time (better for signals)

void handleSignal(int signal) {
    if (signal == SIGINT) {
        std::cerr << "Received SIGINT, preparing to shut down..." << std::endl;
        stopRequested = 1;
    }
}

void configureSignalHandler() {
    signal(SIGINT, handleSignal);
}

bool isFdValid(int fd) {
    if (fd < 0) {
        return false;
    }
    int flags = fcntl(fd, F_SETFL);
    if (flags == -1) {
        return false;
    }
    return true;
}

bool isFdReadyForWrite(int fd, int ret) {
    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLOUT;

    if (ret > 0) {
        if (pfd.revents & POLLOUT) {
            return true;
        }
    }
    return false;
}

void sendHttpErrorResponse(int client_fd, int ret) {

	if (client_fd == 0)
		return ;

    if (!isFdValid(client_fd)) {
        printErrs("Attempting to send to an invalid file descriptor: " + intToString(client_fd));
        return;
    }

    if (!isFdReadyForWrite(client_fd, ret)) {
        printErrs("File descriptor not ready for writing: " + intToString(client_fd));
        return;
    }

    const char* httpResponse =
        "HTTP/1.1 101 Switching Protocols\r\n"
        "Upgrade: websocket\r\n"
        "Connection: Upgrade\r\n"
        "\r\n";

    ssize_t bytesSent = send(client_fd, httpResponse, strlen(httpResponse), 0);
    if (bytesSent < 0) {
        perror("send");
    }
}

// function used to start servers setup _fds and to manage the incoming connection and disconnection on all the servers
bool nginx::startAllServers() {

	if (!verifyImportantServerVal())// verify elementary values of a serverbefore launching
		return false;

    // Configurer le gestionnaire de signaux
    configureSignalHandler();

    try {
        initConnectionSockets();

        while (true) {
			
			// Vérifier si un arrêt est demandé
            if (stopRequested) {
                // Fermer proprement tous les sockets ici
                for (size_t i = 0; i < _fds.size(); ++i) {
                    if (_fds[i].fd != -1) {
                        close(_fds[i].fd);
                    }
                }
				printString("ALL fds has been closed return true");
                return true;
            }

            setAllFdsToPollIn();
			printString("POLLING STARTED");
            size_t ret = poll(_fds.data(), _fds.size(), -1);
			printString("POLLING ENDED");
			printString("RET IS : " + intToString(ret));
            if (ret <= 0) {
				printString("ERROR :: Poll returned " + intToString(ret));
                handlePollErrors(ret);
                continue;
            }

            //size_t processedEvents = 0;
            for (size_t i = 0; i < _fds.size() && ret != 0; i++) {

                if (_fds[i].revents & (POLLIN )) {  //POLLIN) {
					printString(" **** Event on fd : " + intToString(_fds[i].fd) + " index : " + intToString(i) + " & _fds size is " + intToString(_fds.size())+" ***** ");
                    if (processFdEvent(i)) {
                        ret --;
						printString(" ****** ret -- is done ret is now : " + intToString(ret) + " ****** ");
                    }
                }
				if (_fds[i].revents & POLLERR) {
					sendHttpErrorResponse(_fds[i].fd, ret);
					setToBeRemovedValOnClientFd(_fds[i].fd);
					_fds[i].fd = -1;
					printString("ERROR :: POLLERR on fd : " + intToString(_fds[i].fd) + " index : " + intToString(i));
					ret --;
				}
				if (_fds[i].revents & POLLHUP) {
					sendHttpErrorResponse(_fds[i].fd, ret);
					setToBeRemovedValOnClientFd(_fds[i].fd);
					_fds[i].fd = -1;
					printString("ERROR :: POLLHUP on fd : " + intToString(_fds[i].fd) + " index : " + intToString(i));
					ret --;
				}
            }
			printString("BUSSIN");
			removeAndPrint();
        }
        return true;
	} catch (const std::exception &e) {
        std::cerr << "Exception caught in startAllServers: " << e.what() << std::endl;
        return false;
    }
}

void nginx::setAllFdsToPollIn() {
    for (size_t k = 0; k < _fds.size(); k++) {
        _fds[k].events = POLLIN | POLLHUP;
    }
}

void nginx::handlePollErrors(int ret) {
    printErrs("RET ERROR ret is : " + intToString(ret));
    perror("poll");
}

bool nginx::processFdEvent(size_t index ) {
    try {
        for (size_t j = 0; j < _servers.size(); j++) {
            if (_servers[j]->isConnectionSocket(_fds[index].fd) || _servers[j]->isClientSocket(_fds[index].fd)) {
                printString("Executing connection on SERVER ID : ["+intToString(j)+"]");
                _servers[j]->startServer(_fds, index);
				return true;
            }
        }
    } catch (std::exception& e) {
        printErrs(e.what());
    }
    return false;
}
