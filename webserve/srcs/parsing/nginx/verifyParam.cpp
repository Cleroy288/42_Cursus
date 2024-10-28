#include "nginx.hpp"

// FUNTION USE TO VERIFY GENERAL SERV DATA 
bool nginx::verifyParam(const std::string& nameParam, const std::vector<std::string>& params) {
    // Implementation of parameter verification logic
    printString(" ##### Verifying [ " + nameParam + " ] with parameters:");
    for (size_t i = 0; i < params.size(); ++i) {
        printString(" - [" + params[i] + "]");
    }
    if (nameParam == "listen") {// listen int 
       
		if (!verifyListenParam( params )) // Validation pour 'listen'
			return false;

    } else if (nameParam == "server_name") {// server names

		if (!validateServerName( params )) // Validation pour 'server_name'
			return false;
    
	} else if (nameParam == "host") {// ip adress 
       
		if (!validateHost(params)) // Validation pour 'host'
			return false;

    } else if (nameParam == "root") {// site name
        
		if (!validateRoot(params))// Validation pour 'root'
			return false;

    } else if (nameParam == "index") {// html files or htm 
        
		if (!validateIndexFiles(params))// Validation pour 'index'
			return false;

	} else if (nameParam == "client_max_body_size") {// value like 2 m i guess 
        
		if (!validateClientMaxBodySize(params))// Validation pour 'client_max_body_size'
			return false;

	} else if (nameParam == "error_page") {// codes and then a file
        
		if (!validateErrorPageParams(params))// Validation pour 'error_page'
			return false;
    
    } else if ( nameParam == "autoindex" ) {
        
        if (!verifyAutoIndex(params))// validation for auto index
            return false;
    
    }
    else if (  nameParam == "methodes" ) {
        
        if (!verifyMethodesParam(params))// verify if methodes GET POST DELETE are ok
            return false;
    }
    else if ( nameParam == "cgi_timeout" ) {

        if (!verifyCgi_timeout(params))
            return false;

	} else {
        printErrs("Unknown parameter: " + nameParam);
        return false;
    }

    // Example logic: Simply return true for illustration
    return true;
}