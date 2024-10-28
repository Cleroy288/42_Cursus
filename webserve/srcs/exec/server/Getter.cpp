#include "../../parsing/server/server.hpp"

std::string server::getErrorAndPages( int errorVal ) {

	if (_errorCodeAndPages.empty())
		return "";
	for (size_t i = 0; i < _errorCodeAndPages.size(); i++) {
		
		for (size_t j = 0; j < _errorCodeAndPages[i].errorCodes.size(); j++) {
			
			if (errorVal == _errorCodeAndPages[i].errorCodes[j])
				return _errorCodeAndPages[i].fileToRedirectTo;
		}
	}
	return "";
}

// std::string server::getErrorAndPages( int& errorVal ) {

// 	if (_errorCodeAndPages.empty())
// 		return "";
// 	for (size_t i = 0; i < _errorCodeAndPages.size(); i++) {
		
// 		for (size_t j = 0; j < _errorCodeAndPages[i].errorCodes.size(); j++) {
			
// 			if (errorVal == _errorCodeAndPages[i].errorCodes[j])
// 				return _errorCodeAndPages[i].fileToRedirectTo;
// 		}
// 	}
// 	return "";
// }

std::string server::getErrorAndPages( int errorVal, std::string locationName ) {
	if (locationName == "")
		return (getErrorAndPages(errorVal));
	if (_locationData.empty())
		return (getErrorAndPages(errorVal));
	for (size_t i = 0; i < _locationData.size(); i++) {

		if (_locationData[i]._location == locationName ) {
			
			for ( size_t j = 0; j < _locationData[i]._nameAndParam.size(); j++ ) {
				
				if (_locationData[i]._nameAndParam[j].first == "error_page") {
					
					for( size_t k = 0; k < _locationData[i]._nameAndParam[j].second.size(); k++ ) {
						
						if ( std::atoi(_locationData[i]._nameAndParam[j].second[k].c_str()) == errorVal) {
							size_t index = _locationData[i]._nameAndParam[j].second.size();
							return _locationData[i]._nameAndParam[j].second[index - 1];
						}
					}	
				}
			}
		}
	}
	return (getErrorAndPages(errorVal));
}

// std::string server::getErrorAndPages( int& errorVal, std::string& locationName ) {
// 	if (locationName == "")
// 		return (getErrorAndPages(errorVal));
// 	if (_locationData.empty())
// 		return "";
// 	for (size_t i = 0; i < _locationData.size(); i++) {

// 		if (_locationData[i]._location == locationName ) {
			
// 			for ( size_t j = 0; j < _locationData[i]._nameAndParam.size(); j++ ) {
				
// 				if (_locationData[i]._nameAndParam[j].first == "error_page") {
					
// 					for( size_t k = 0; k < _locationData[i]._nameAndParam[j].second.size(); k++ ){
						
// 						if ( std::atoi(_locationData[i]._nameAndParam[j].second[k].c_str()) == errorVal) {
// 							size_t index = _locationData[i]._nameAndParam[j].second.size();
// 							return _locationData[i]._nameAndParam[j].second[index - 1];
// 						}
// 					}	
// 				}
// 			}
// 		}

// 	}
// 	return "";
// }


// Helper function to split string by delimiter
std::vector<std::string> split(const std::string& str, char delim) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (getline(tokenStream, token, delim)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

// Function to find the name of the location based on URL
std::string server::getNameOfLocationBAsedOnURL( std::string& URL) {
    // Find the first '/' after "http://" or "https://"
    std::size_t start = URL.find("//");
    if (start != std::string::npos) {
        start = URL.find('/', start + 2);
    } else {
        start = URL.find('/');
    }

    if (start == std::string::npos) return ""; // No '/' found

    // Check if it's the root directly
    if (start + 1 == URL.length()) {
        // Check for the root location '/'
        for (size_t j = 0; j < _locationData.size(); ++j) {
            if (_locationData[j]._location == "/") {
                return "/"; // Root location found
            }
        }
    }

    // Get the path part of the URL after the domain
    std::string path = URL.substr(start);

    // Split the path on '/'
    std::vector<std::string> segments = split(path, '/');

    // Try to match segments with known locations
    if (!segments.empty()) {
        std::string location = "/" + segments[0];
        for (size_t j = 0; j < _locationData.size(); ++j) {
            if (_locationData[j]._location == location) {
                return location; // Match found
            }
        }
    }

	for (size_t i = 0; i < _locationData.size(); i++) {
		if (_locationData[i]._location == "/")
			return "/";
	}

    return ""; // No matching location found
}
/*
creer une function bool isAutoIndexOn(location) : renvoie true ou false si
l'autoindex est active ou non en function de la location et genre il faut regarder
dans la location et dans les regles de base il me semble mais pas sur
*/
// go see if there is autoindex on in a location based on name
bool server::isAutoIndexOnInLoc( std::string locationName ) {
	for ( size_t i = 0; i < _locationData.size(); i++ ) {
		if ( _locationData[i]._location == locationName ){
			//printString("Location : " + locationName + " is found.");
			for (size_t j = 0; j < _locationData[i]._nameAndParam.size(); j++ ) {
				if (_locationData[i]._nameAndParam[j].first == "autoindex") {
					std::string namePar = _locationData[i]._nameAndParam[j].first;
					//printString("first is : " + namePar);
					for (size_t k = 0; k < _locationData[i]._nameAndParam[j].second.size() ; k++) {
						std::string param = _locationData[i]._nameAndParam[j].second[k];
						//printString("@ sec param : " + param);
						if (_locationData[i]._nameAndParam[j].second[k] == "on;")
							return true;
					}
				}
			}
		}
	}
	return false;
}

// go see if there is autoindex on in a gen part of a server, return true if there is and false if there is not
bool 	server::isAutoIndexOnInGen(  ) {
	if (_autoIndex != "def")
		return true;
	else 
		return false;
}

std::string server::getAutoIndexGenVal() {
	if (_autoIndex != "def")
		return _autoIndex;
	else
		return "";
}

/*
Tu sais me faire une fonction getAllowedMethod(la methode en string,
location en string) et elle doit me renvoyer en function de la methode
que je passe si la methode est possible ou non en fonction de la location merci 
*/
/*
Tu sais me faire une fonction getAllowedMethod(la methode en string,
location en string) et elle doit me renvoyer en function de la methode
que je passe si la methode est possible ou non en fonction de la location merci 
*/


bool 	server::getAllowedMethod( std::string method, std::string location ) {
	if (method == "autoindex") {
		if (isAutoIndexOnInLoc(location) == true)
			return true;
		else
			return false;
	}
	else {
		for ( size_t i = 0; i < _locationData.size(); i++ ) {
			//printString("location :: [" + _locationData[i]._location + "]");
			if ( _locationData[i]._location == location ) {
			//	printString("location found : " + location);
				for ( size_t j = 0; j < _locationData[i]._nameAndParam.size(); j++ ) {
					if (_locationData[i]._nameAndParam[j].first == "methodes") {
			//			printString("methodes found");
						for (size_t k = 0; k < _locationData[i]._nameAndParam[j].second.size(); k++) {
							std::string word = removeCharacter(_locationData[i]._nameAndParam[j].second[k], ';');
							if (word/*_locationData[i]._nameAndParam[j].second[k]*/ == method) {
			//					printString("method : " + method + " was found in " + location);
								return true;
							}
						}
						return false;
					}
				}
			}
		}
		if (_methodes.empty())// if no methods are found in location && _methods are empty return true
			return true;
		for (size_t i = 0; i < _methodes.size(); i++) {// look for method in _methods
			if (_methodes[i] == method)
				return true;
		}
		std::cerr << "Method not found in location, checking in server" << std::endl;
		// si pas de location verifie dans les regles de base/server
	}
	return true;
}
/*
std::string getRoot(location) : qui envoie le chemin du dossier ou on est semse entre en
function de la location et si il n'y a pas on doit respecter la root de base 🙂 pour qu'on puisse faire un chdir
*/
std::string server::getRootInLoc( std::string location ) {
	for ( size_t i = 0; i < _locationData.size(); i++ ) {
		if ( _locationData[i]._location == location ) {
			printString("location found : " + location);
			for ( size_t j = 0; j < _locationData[i]._nameAndParam.size(); j++ ) {
				if (_locationData[i]._nameAndParam[j].first == "root") {
					printString("root found in : " + location + " param is : " + _locationData[i]._nameAndParam[j].second[0]);
					return _locationData[i]._nameAndParam[j].second[0];
				}
			}
		}
	}
	return "";
}

// same function but for gen part 
std::string server::getRoot() {
	printString("getRoot sending back root in gen part");
	return _root;
}

std::vector<std::string> server::getIndexOfLocation(std::string locationName) {
	
	std::vector<std::string> ret ;
	for (size_t i = 0; i < _locationData.size(); i++) {
		
		if (_locationData[i]._location == locationName) {
			
			if (std::find( _locationData[i]._params.begin(), _locationData[i]._params.end(), "index" ) != _locationData[i]._params.end()) {
				
				for (size_t j = 0; j < _locationData[i]._nameAndParam.size(); j++) {
					
					if (_locationData[i]._nameAndParam[j].first == "index") {

						printString("index of location data : " + locationName + " has been found");
						ret = _locationData[i]._nameAndParam[j].second;
						
						return removeCharFromVec(ret, ';');
					}
				}
			} else {
				printString("no index files found in location data : " + locationName);
				ret =_indexFiles;
				return removeCharFromVec(ret, ';');
			}
		}
	}
	printString("no index files found in location data : " + locationName);
	ret = _indexFiles;
	return removeCharFromVec(ret, ';');
}

// function asked by Hugo , sends back the redirr param in à location if nothing is found return snothing ("")
std::string server::getRedirrectLocation(std::string location) {
	
	if (getAllowedMethod("redirr", location)) {
		
		for (size_t i = 0; i < _locationData.size(); i++) {
	
			if (_locationData[i]._location == location) {// location given 
	
				std::vector<std::string>::iterator it = std::find(_locationData[i]._params.begin(), _locationData[i]._params.end(), "redirr");
				if (it != _locationData[i]._params.end()) {// if right param is found
	
					for (size_t j = 0; j < _locationData[i]._nameAndParam.size(); j++) {
	
						if (_locationData[i]._nameAndParam[j].first == "redirr") {
							return removeCharacter( _locationData[i]._nameAndParam[j].second[0], ';' );
						}
					}
				}
			}
		}
	}
	return "";
}