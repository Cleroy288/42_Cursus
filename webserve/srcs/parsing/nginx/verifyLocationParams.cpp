#include "nginx.hpp"

std::string getFirstWord(const std::string& str) {
    // Trouver la position du premier espace
    std::size_t pos = str.find(' ');
    // Extraire et retourner le premier mot
    if (pos != std::string::npos) {
        return str.substr(0, pos);
    }
    // Si aucun espace n'est trouvé, retourner toute la chaîne
    return str;
}


std::string getRestAfterFirstSpace(const std::string& str) {
    // Trouver la position du premier espace
    std::size_t pos = str.find(' ');
    // Extraire et retourner la sous-chaîne après le premier espace
    if (pos != std::string::npos && pos + 1 < str.size()) {
        return str.substr(pos + 1);
    }
    // Si aucun espace n'est trouvé, ou si rien n'est après l'espace, retourner une chaîne vide
    return str;
}

/**

root - Specifies the root directory for requests.
Values: Path, e.g., /var/www/html
index - Defines files that will be used as indexes.
Values: Filenames, e.g., index.html, index.htm, index.php
try_files - Tries to serve the requested file and falls back to others if not found.
Values: Paths, e.g., $uri, $uri/, /index.html
error_page - Defines the URI that will be shown for specific errors.
Values: Status codes and paths, e.g., 404 /404.html
client_max_body_size - Limits the size of the client request body.
Values: Size in bytes or formatted like 2k, 2m
autoindex - Enables or disables the directory listing.
Values: on, off
deny - Denies access to certain IP addresses.
Values: IP address, all
allow - Allows access to certain IP addresses.
Values: IP address, all
return - Returns a specified status code and text or redirects.
Values: Status code and text or URL, e.g., 301 http://example.com
rewrite - Rewrites a request URL based on specified regular expressions and replacement.
Values: Regex and replacement string, e.g., ^(/download/.*)/media/(.*)\..*$ $1/mp3/$2.mp3
set - Sets the value of a variable.
Values: Variable name and value, e.g., $variable value
proxy_pass - Defines the protocol and address of a proxied server and an optional URI.
Values: URL, e.g., http://localhost:8000
fastcgi_pass - Sets the address of a FastCGI server.
Values: Socket or IP address and port, e.g., unix:/var/run/php5-fpm.sock
limit_except - Allows limiting access to certain HTTP methods.
Values: HTTP methods, e.g., GET, POST

**/

// all valid params for location params
std::vector<std::string> isValidParam( ) {

    std::vector<std::string> _possibleParam;

    _possibleParam.push_back("root");
    _possibleParam.push_back("client_max_body_size");
    _possibleParam.push_back("error_page");
    _possibleParam.push_back("autoindex");
    _possibleParam.push_back("methodes");
    _possibleParam.push_back("cgi_pass");
    _possibleParam.push_back("redirection");
    _possibleParam.push_back("index");
    _possibleParam.push_back("redirr");

    return _possibleParam;
} 

bool verifyNameParamWithValidParam( std::string nameParam ) {
    std::vector<std::string> possibleParam = isValidParam();// set all possible lo params incontainer
    if ( std::find( possibleParam.begin(), possibleParam.end(), nameParam ) == possibleParam.end()) {
        printString("(verifyNameParamWithValidParam) error no valid param of name : [" + nameParam +"] found in list");
        return false;
    }
    return true;
}

bool verifyIfParamsAreValid(std::string nameParam, std::vector<std::string> params) {

    printString("verifyIfParamsAreValid doing : " + nameParam );
    // verify of params are valid based on name of nameParam
    if (nameParam == "root") {
        if (!isValidRootPath(params[0]))
            return false;

    } else if (nameParam == "client_max_body_size") {
    	
        if (!validateClientMaxBodySize(params))// Validation pour 'client_max_body_size'
		    return false;

    } else if (nameParam == "error_page") {

		if (!validateErrorPageParams(params))// Validation pour 'error_page'
			return false;

    } else if (nameParam == "autoindex") {
        
        if (!verifyAutoIndex(params))// validation for auto index
            return false;

    } else if (nameParam == "methodes") {

        if (!verifyMethodesParam(params))// verify if methodes GET POST DELETE are ok
            return false;

    } else if (nameParam == "cgi_pass") {// verify if cgi_pass is ok

        if (!verifyCgiPass(params))
            return false;

    } else if ( nameParam == "redirection" ) {

        if (!validateIndexFiles(params))// Validation pour 'index' is the same as 'redirection' i guess 
			return false;

    }
    else if (nameParam == "index") {// html files or htm 
        
		if (!validateIndexFiles(params))// Validation pour 'index'
			return false;

    } 
    else if (nameParam == "redirr") {

        if (!validateIndexFiles(params))// Validation pour 'index' is the same as 'redirection' i guess 
			return false;

    } else {
        printString("(verifyIfParamsAreValid) unknow nameParam is found, could not prcess it's params");
        return false;
    }
    return true;
}

// sort the paras of location in paramName and Params
bool sortParamsInNameAndParams( std::vector<std::string> params ) {
    std::string nameNewParam;
    std::vector<std::string> NewParms;
    bool newName = true;

    for (size_t i = 0; i < params.size(); i++) {
        if ( newName == true ) {// set juste a new name
            nameNewParam = params[i];
            newName = false;
            //continue;
        } else {
            NewParms.push_back( params[i] );
            if (endsWithSemicolon(params[i])) {// if we are at last value 
                
                // verify Param and Params 
                if (!verifyNameParamWithValidParam(nameNewParam))
                    return false;
                if (!verifyIfParamsAreValid(nameNewParam, NewParms))
                    return false;
                
                // set back new name
                newName = true;
                // clear paramName and params
                NewParms.clear();
                nameNewParam.clear();
                continue;
            }
        }
    }
    return true;
}

bool verifyNameParamAndParams(std::string nameParam, std::vector<std::string> params) {

    printString("(verifynameParamParams) location trying to do : " + nameParam);

    if (!sortParamsInNameAndParams(params))// function to devideparams in params and name and verify them 
        return false;

    // verify if name of location is valid or not 
    if (!isValidLocationPath(nameParam))
        return false;

    return true;
}

bool nginx::verifyLocationParams(std::vector<std::string> _tokenizedNgixContent) {
    int                         braceCount = 0;
    bool                        inLoc = false;
    bool                        inDirectiveBlock = false; // Flag to manage directive-specific blocks
    std::string                 nameParam;// name of location
    std::string                 extraQual;// modifyer of location
    std::vector<std::string>    params;// content of location 

    //printString("********* Location verification **********");
    printString("=====================================================");
    std::cout << "===&&& |[ START LOCATION PARAM VERIFICATION ]| &&&===" << std::endl;
    printString("=====================================================");

    for (size_t i = 0; i < _tokenizedNgixContent.size(); ++i) {
        std::string word = _tokenizedNgixContent[i];
        if (word == "location" && inLoc == false) {
            inLoc = true;
            continue;
        }
        if (word != "{" && word != "}" && inLoc == true && nameParam.empty()) {
            nameParam = word;
            //printString("name param is : " + nameParam);
            continue;
        }
        if (word != "{" && word != "}" && inLoc == true && !nameParam.empty() && braceCount == 0)
        {
            nameParam +=" "+word;
            //printString("had to cat name param, new name param is : " + nameParam);
            continue;
        }
        if (word == "{" && inLoc == true ) {
            if (braceCount == 1 && inDirectiveBlock == false) {
                inDirectiveBlock = true;
                //printString("in directive block : " + word);
            }
            braceCount++;
        }
        if ( word == "}" && inLoc == true ) {
            if ( inDirectiveBlock == true && braceCount == 2)
                inDirectiveBlock = false;
            braceCount--;
        }
        if (inLoc == true && braceCount > 0 && braceCount > 2) {
            extraQual = word;
            continue;
        }
        if (inLoc == true && braceCount > 0 && braceCount <= 2 ) {
            if (word != "{" && word != "}") {
                params.push_back(word);
            }
            word.clear();
            continue;
        }
        if (braceCount == 0 && !nameParam.empty() && inLoc == true ) {
            // verify the params !! 
			extraQual = getFirstWord(nameParam);
			if (extraQual == nameParam) { 
				extraQual.clear();
			}
			nameParam = getRestAfterFirstSpace(nameParam);

            printString("extra qual [" + extraQual + "] and name param : "+"[" + nameParam + "]"); 
            if (!isValidModifyer(extraQual) )// verify modifyer and name of param
                return false;
            //printString("params : ");
            //for (size_t i = 0; i < params.size(); i++) {
            //    printString("- *|"+params[i]+"|* -");
            //}
            if (!verifyNameParamAndParams( nameParam, params ) )
                return false;
			
            nameParam.clear();
			extraQual.clear();
            inLoc = false;
            //printString("out loc condition with word : " + word);
            params.clear();
            continue;
        }
    }
    printString("================================================");
    std::cout << "===&&& |[ ALL LOCATION PARAM ARE VALID ]| &&&===" << std::endl;
    printString("================================================");
    return true;
}