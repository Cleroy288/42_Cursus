#include "server.hpp"

// set the value of _errorCodeAndPages
void server::findErrorPageAndCodes() {

	bool			foundErrorPages = false; // button use to see if we are have found error_pages

	std::string		line; // treat data 
	errorAndPages	tmp; // use to then be set in server structure 
	

	for (size_t index = 0; index < this->_content.size(); index++) {

		// line we will use to treat data
		line = this->_content[index];
		
		if (line.find("error_page") != std::string::npos) {
			// error_page found 
			foundErrorPages = true;
			continue;
		}
		// we found and error page and are still in a valid flow of data 
		else if (foundErrorPages == true) {

			// find ; wich mean we are at end of line we have to treat
			size_t pos = line.find(';');
			
			// we are in the last word cuz we found ';'
			if (pos != std::string::npos) {
				
				// find file / html page
				tmp.fileToRedirectTo = line;
				// still push the last line / word cuz it's still valid
				this->_errorCodeAndPages.push_back(tmp);

				// reinitialize button and temporary structure
				foundErrorPages = false;
				tmp.errorCodes.clear();
			}
			else {
				// push number to the error_codes
				tmp.errorCodes.push_back( std::atoi( line.c_str() ) );
			}
		}
	}
}

// find _root, _host, _listen,  _maxRequestBody
// ## NOTE:: findDATA only find the first occurence of the searched data , so not adapted for every use
void	server::findData( const std::string &nameData ) {
	
	// string we are going to use to better treat data
	std::string word;
	// simple button to know if we are in a valid flow of data 
	bool		on = false;

	for (size_t i = 0; i < this->_content.size(); i++) {
		word = this->_content[i];
		if (word == nameData) {
			on = true;
		}
		else if (on == true) {
			if (nameData == "root")
				this->_root = word;
			//else if (nameData == "listen")
			//	this->_listen = std::atoi(word.c_str());
			else if (nameData == "host")
				this->_host = word;
			else if (nameData == "client_max_body_size")
				this->_maxRequestBody = word;
			else if (nameData == "autoindex")
				this->_autoIndex = word;
			else if (nameData == "cgi_timeout")
				this->_cgi_timeout = word;
			on = false;
			return ;
		}
	}
}

void	makeNameAndParam( std::vector< std::pair< std::string, std::vector<std::string> > > &NameAndParam, std::string &res) {

	std::string name;
	std::string param;
	size_t		index;
	std::string	token;
	std::vector<std::string> params;

	index = res.find(' ');
	name = res.substr(0, index);
	param = res.substr(index, res.size());

	std::istringstream iss(param);

	while (iss >> token) {
		params.push_back(token);
	}
	
	NameAndParam.push_back(std::make_pair(name, params));
	
	//for (size_t i = 0; i < NameAndParam.size(); i++) {
	//	printString("index : " + std::to_string(i));
	//	printString("name - " + NameAndParam[i].first);
	//	for (size_t j = 0; j < NameAndParam[i].second.size(); j++) {
	//		printString("param - " + NameAndParam[i].second[j]);
	//	}
	//}
	//printString("------ end of this node ------ ");
}

// find and set _location data 
void server::setLocation() {

	// every node of _locationData has :
	// - location ( the location '/' part )
	// - params ( all the name of the params found in and location part )
	// - nbrOfParam (number of parameters found in the location part of this node )
	// - nameAndParam ( contains the name and the value of each parameter )

	bool	inLoc = false;
	int		inBrace = 0;
	int		nbrOfParamInLoc = 0;
	std::string res;
	std::string path;

	// try to do some stuff, not really important just used to catch errors
	try {

		locationData tmpLocData;

		for (size_t i = 0; i < _content.size(); i++) {

			std::string word = _content[i];
			if (word == "location") {
				inLoc = true;
			}
			else if (inLoc == true) {
				if (inBrace == 0 && word != "{" && word != "}") {
					//if (!path.empty()) {
					//	//printString("error worong modifyer : " + path);
					//	throw std::runtime_error("error worng modifyer : " + path);
					//}
					if (word == "~" || word == "^~" || word == "~*" || word == "~" || word == "~*" || word == "=" || word == "@") {
						tmpLocData._modifyer = word;
					} else {
						path = path + word;
					}
				}
				if (inBrace == 0 && word == "{") {	
					tmpLocData._location = path;// path 					
					path = "";// reset path
				}
				if (word == "{")// increment 
					inBrace ++;
				else if (word == "}") {// decrement
					inBrace --;
					if (inBrace == 0) {// we are at end of brace location {...}
						inLoc = false;
						res = "";
												
						tmpLocData._nbrOfParam = nbrOfParamInLoc;// nbr of params 
		
						// set data in _locationData
						_locationData.push_back(tmpLocData);

						// try reset 
						tmpLocData._location = "";
						tmpLocData._nbrOfParam = 0;
						tmpLocData._params.clear();
						tmpLocData._nameAndParam.clear();
						tmpLocData._modifyer.clear();

						nbrOfParamInLoc = 0;
					}
				}
				if (inBrace > 0 ) { // in brace, wich mean we have passed an '{' character
					
					size_t pos = word.find(';');// see it we are at the last param due to ';'
					
					if ( word != "}" && word != "{" ) {// if we are in valid location { ... } brace
						res = res + "" + word + " ";// add content to res
					}
					if (pos != std::string::npos) { // if there is an ';' , wich mean we are in last argument
						
						tmpLocData._params.push_back(extractFirstWord(res));// we push the name of val, wich is the first word 
						makeNameAndParam( tmpLocData._nameAndParam, res);// we make a list of the rest of the values to be put in sec value of pair in _nameAndParam

						nbrOfParamInLoc++; // increment the number of params in location part 
						res = ""; // reinitialize the res value 
						continue;
					}
				}
			}
		}
		//printString("-- end --");
	}
	catch( std::exception &e ) {
		printErrs( e.what() );
		throw std::runtime_error("Error in set location");
		//return ;
	}
}

// function to verify if set port is valid
bool 	isValidPort( int port ) {
	return port > 0 && port <= 65535;// valid plage of ports
}

// function to find _listen and _indexFiles and _serverName
void server::putInWord( std::string word ) {
	
	std::string 	token;
	bool 			foundKeyWord = false;

	for( size_t i = 0; i < _content.size(); i++ ) {// go through content 
		
		token  = _content[i];// token found 

		if ( token == word && !foundKeyWord ) {// index found
			foundKeyWord = true;// set button on 
			continue;// go on 
		}
		if (foundKeyWord) {// index is found
			if ( token.find(';') != std::string::npos) {// last word found 
				token = token.substr(0, token.size() - 1);// remove ';';
				if (word == "listen") {
					long int port = std::atoi( token.c_str() );
					if (isValidPort(port))// verify if is a valid port
						_listen.push_back( token );// push last word without ';'
					else
						printErrs("Error invalid port found, port : " + token + " is not a valid port, this one wil be skipped");
				}
				else if (word == "index")
					_indexFiles.push_back( token );// push last word without ';'
				else if (word == "server_name")
					_serverName.push_back( token );// push last word without ';'
				else if (word == "methodes")
					_methodes.push_back(token);
				foundKeyWord = false;// we are on last word 
				break ;
			}
			else {// else juste push token
				if (word == "listen") {// if isten if found
					long int port = std::atoi(token.c_str());
					if (isValidPort(port))
						_listen.push_back(token);
					else
						printErrs("Error invalid port found, port : " + token + " is not a valid port, this one wil be skipped");
				}
				else if (word == "index")
					_indexFiles.push_back(token);
				else if (word == "server_name")
					_serverName.push_back(token);
				else if (word == "methodes")
					_methodes.push_back(token);
			}
		}
	}

	// print and verify
	//if (word == "index") { 
	//	for ( size_t i = 0; i < _indexFiles.size(); i++ ) {
	//		printString("index files found : " + _indexFiles[i]);
	//	}
	//}
	//else if (word == "listen") {
	//	for ( size_t i = 0; i < _listen.size(); i++ ) {
	//		printString("listen found : " + _listen[i]);
	//	}
	//}
	//else if (word == "server_name") {
	//	for ( size_t i = 0; i < _serverName.size(); i++) {
	//		printString("server name found : " + _serverName[i]);
	//	}
	//}
}

// default constructor in wich all the server part except _clients is set 
server::server( const std::vector<std::string> &serverInfo, size_t index ) {

	printString(" ---- server default constructor called ---- ");

	// immediately done 
	this->_content = serverInfo;
	this->_index = index;


	/****   TODO  ********/
	std::string def= "def";
	//this->_serverName = def;
	//this->_listen = 0; // DONE  , 0 is def val 
	this->_host = def; // DONE , def is default val
	this->_root = def; // DONE , def is default val
	this->_maxRequestBody = def; // DONE, def is default val
	this->_autoIndex = def; 

	//this->_errorCodeAndPages = DONE;
	// this->_indexFiles = DONE;
	// this->_clients --> set later when the 
	/********************/


	// find and set _errorCodeAndPages
	findErrorPageAndCodes();
	// used to see if there is _errorCodeAndAPgesSet	
	//for (size_t i = 0; i < _errorCodeAndPages.size(); i++) {
//
	//	printString(" --- index : " + std::to_string(i));
	//	printString("file : " + _errorCodeAndPages[i].fileToRedirectTo);
	//	
	//	for (size_t j = 0; j < _errorCodeAndPages[i].errorCodes.size(); j++) {
	//		printString("error code : " + std::to_string( _errorCodeAndPages[i].errorCodes[j] ));
	//	}
	//}


	// find _host
	findData("host");
	//printString( "host ==> "+_host);
		
	// find _root
	findData("root");
	// printString( "root ==> "+_root);

	// find _maxRequestBody
	findData("client_max_body_size");
	//printString("max body ==> " + _maxRequestBody);

	// find autoIndex / autoindex
	findData("autoindex");

	// fin cgi timeout
	findData("cgi_timeout");

	// set _locationData
	setLocation();

	// set _listen and _indexFiles
	putInWord("listen");
	putInWord("index");
	putInWord("server_name");
	putInWord("methodes");// OK
	//if (_methodes.empty())
	//	printString("methodes is empty");
	//else
	//	for (size_t i = 0; i < _methodes.size(); i++) {
	//		printString(_methodes[i]);
	//	}
//
	//exit(EXIT_FAILURE);

	//printString( "index :: "+std::to_string(index) );
//
	//printString(" --- ##### START ##### --- ");
	//for (size_t i = 0; i < _locationData.size(); i++) {
	//	
	//	printString(" ##### index : " + std::to_string(i) + " ##### ");
	//	printString(" ##### _location : " + _locationData[i]._location + " ##### ");
	//	printString(" ##### _modifyer : " + _locationData[i]._modifyer + " ##### ");
	//	printString(" ##### number of params : " + std::to_string(_locationData[i]._nbrOfParam) + " ##### ");
	//	printString(" ##### _params ##### ");
	//	for (size_t j = 0; j < _locationData[i]._params.size(); j++) {
	//		printString("param [" + std::to_string(j) + "]" + " : "+_locationData[i]._params[j]);
	//	}
//
	//	printString(" ##### _nameAndParam ##### ");
	//	for (size_t k = 0; k < _locationData[i]._nameAndParam.size(); k++) {
	//		
	//		printString("name : " + _locationData[i]._nameAndParam[k].first);
//
	//		for (size_t j = 0; j < _locationData[i]._nameAndParam[k].second.size(); j++) {
	//			printString("param : " + _locationData[i]._nameAndParam[k].second[j]);
	//		}
	//	}
//
	//	printString("");
	//
	//}
	//printString(" --- ##### END ##### --- ");
//
	//printString("TESSSST ");
	//printString("CGI ::: " + intToString(getCgi_timeout()));
	//printString("MAX REQ ::: " + intToString(getMaxRequestBody()));

	//printString("TEST --->");
	//std::vector<std::string> ret = getIndexOfLocation("/");
	//printvec(ret);
	//printString("end <----");
	//exit(EXIT_FAILURE);
}

server::~server() {

	printString("Server default destructor called");
 
    for (size_t i = 0; i < _connectionSocket.size(); i++) {
		std::string nbr = intToString(_connectionSocket[i]->getSocketFd());
		printString("Socket who listens on fd : " + nbr + " is destroyed");
        delete _connectionSocket[i]; // Libérez chaque socket alloué dynamiquement
		_connectionSocket[i] = NULL; // Set the pointer to NULL after deletion

    }
	for (size_t i = 0; i < _clients.size(); i++) {
		//std::string nbr = intToString(_clients[i]->getSocketFd());
		printString("client killed");
        delete _clients[i]; // Libérez chaque socket alloué dynamiquement
		_clients[i] = NULL; // Set the pointer to NULL after deletion

    }
	_clients.clear();
	
	_connectionSocket.clear(); // Optional: clear the vector for safety
}

size_t server::getId() {
	return _index;
}