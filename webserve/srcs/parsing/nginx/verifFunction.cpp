#include "../../../includes/principal.hpp"
#include "./nginx.hpp"

// LISTEN
bool isInt(const std::string& str) {
    char* endPtr;
    long val = std::strtol(str.c_str(), &endPtr, 10); // Conversion en long

    if (*endPtr != '\0' || str.empty()) {
        return false; // Pas un entier complet
    }

    return val >= 0 && val <= 65535; // Port valide entre 0 et 65535
}

bool isIpAddress(const std::string& str) {
    // Implementation simple de la validation d'une adresse IP
    std::istringstream iss(str);
    std::string byte;
    int count = 0;
    while (getline(iss, byte, '.')) {
        if (!isInt(byte) || ++count > 4) {
            return false;
        }
    }
    return count == 4; // Doit avoir exactement 4 octets
}

bool verifyListenParam(std::vector<std::string> params) {
    bool hasValidPort = false; // Nous devons au moins trouver un port valide

    for (size_t i = 0; i < params.size(); i++) {
        std::string param = params[i];

        // Vérifie si c'est un numéro de port
        if (isInt(param)) {
            hasValidPort = true; // Marque qu'un port valide a été trouvé
        } else {
            // Vérifie les options spécifiques de Nginx pour listen
            if (param != "default_server" && param != "ssl" && !isIpAddress(param)) {
                return false; // Retourne faux si l'option n'est pas reconnue
            }
        }
    }

    return hasValidPort; // Assure qu'au moins un port valide a été spécifié
}

// SERVER_NAME 
bool isValidDomainSuffix(const std::string& domain) {
    static const char* validSuffixes[] = {".com", ".net", ".org", ".be", ".co.uk", ".eu", NULL};
    for (const char** suffix = validSuffixes; *suffix != NULL; ++suffix) {
        if (domain.length() >= strlen(*suffix) &&
            domain.compare(domain.length() - strlen(*suffix), strlen(*suffix), *suffix) == 0) {
            return true;
        }
    }
    return false;
}

bool containsOnlyValidCharacters(const std::string& domain) {
    for (size_t i = 0; i < domain.length(); ++i) {
        char ch = domain[i];
        if (!isalnum(ch) && ch != '-' && ch != '.' && ch != '_') {
            return false;
        }
    }
    return true;
}

bool validateServerName(const std::vector<std::string>& serverNames) {
    for (size_t i = 0; i < serverNames.size(); ++i) {
        const std::string& domain = serverNames[i];
        if (!containsOnlyValidCharacters(domain) || domain.find('.') == std::string::npos || !isValidDomainSuffix(domain)) {
            std::cerr << "Invalid domain name: " << domain << std::endl;
            return false;
        }
    }
    return true;
}

// HOST 
bool isValidIpAddress(const std::string& ipAddress) {
    std::istringstream stream(ipAddress);
    std::string token;
    int count = 0;
    while (std::getline(stream, token, '.')) {
        if (token.empty() || token.size() > 3) {
            return false;
        }
        for (size_t i = 0; i < token.size(); ++i) {
            if (!isdigit(token[i])) {
                return false;
            }
        }
        int num = atoi(token.c_str());
        if (num < 0 || num > 255) {
            return false;
        }
        ++count;
    }
    return count == 4; // An IP address must consist of four octets
}

bool validateHost(const std::vector<std::string>& params) {
    if (params.empty()) {
        std::cerr << "No IP address provided for host." << std::endl;
        return false;
    }
    if (!isValidIpAddress(params[0])) {
        std::cerr << "Invalid IP address: " << params[0] << std::endl;
        return false;
    }
    return true;
}

// ROOT 
bool isValidRootPath(const std::string& path) {
    if (path.empty()) {
        std::cerr << "Root path is empty." << std::endl;
        return false;
    }
    if (path[0] != '/') {
        std::cerr << "Root path must start with '/'." << std::endl;
        return false;
    }
    // Additional checks can be added here, e.g., checking for illegal characters
    return true;
}

bool validateRoot(const std::vector<std::string>& params) {
    if (params.empty()) {
        std::cerr << "No root path provided." << std::endl;
        return false;
    }
    if (!isValidRootPath(params[0])) {
        std::cerr << "Invalid root path: " << params[0] << std::endl;
        return false;
    }
    std::cout << "Valid root path: " << params[0] << std::endl;
    return true;
}

// INDEX
// Helper function to check if a filename ends with a valid web file extension
bool hasValidWebExtension(const std::string& filename) {
    std::string::size_type dotPosition = filename.rfind('.');
    if (dotPosition == std::string::npos) {
        std::cerr << "File '" << filename << "' has no extension." << std::endl;
        return false;
    }
    
    std::string extension = filename.substr(dotPosition);
	extension = removeCharacter(extension, ';');// remove ';' if there is one 
    // Check against a list of valid extensions
    if (extension == ".html" || extension == ".htm" || extension == ".php" || extension == ".jsp") {
        return true;
    } else {
        std::cerr << "File '" << filename << "' has an invalid extension: " << extension << std::endl;
        return false;
    }
}

// Function to validate all index file entries in a vector
bool validateIndexFiles(const std::vector<std::string>& params) {
    for (std::vector<std::string>::const_iterator it = params.begin(); it != params.end(); ++it) {
        if (!hasValidWebExtension(*it)) {
            std::cerr << "Invalid index file: " << *it << std::endl;
            return false;
        }
    }
    std::cout << "All index files are valid." << std::endl;
    return true;
}

// CLIENTS_MAX_BODY_SIZE
// Helper function to check if the size specification is valid
bool isValidSizeSpec( const std::string& sizeSpec) {
    // Vérifie que la chaîne n'est pas vide
    if (sizeSpec.empty()) {
        return false;
    }
	std::string newSizeSpec = removeCharacter(sizeSpec, ';');//remove if there is one 
    // Vérifie que tous les caractères de la chaîne sont des chiffres
    for (size_t i = 0; i < newSizeSpec.length(); ++i) {
        if (!std::isdigit(newSizeSpec[i])) {
            return false;
        }
    }

    return true;
}

// Function to validate the 'client_max_body_size' parameter
bool validateClientMaxBodySize(const std::vector<std::string>& params) {
    if (params.empty()) {
        std::cerr << "No parameters provided for client_max_body_size." << std::endl;
        return false;
    }

    for (size_t i = 0; i < params.size(); ++i) {
        if (!isValidSizeSpec(params[i])) {
            std::cerr << "Invalid client_max_body_size: " << params[i] << std::endl;
            return false;
        }
    }

    std::cout << "All client_max_body_size parameters are valid." << std::endl;
    return true;
}

// ERROR_PAGE
// Helper function to check if a string is a valid HTTP status code
bool isValidHttpStatusCode(const std::string& code) {
    int statusCode = std::atoi(code.c_str());
    return statusCode >= 100 && statusCode <= 599;
}

// Helper function to check if a string is a valid file path for an HTML file
bool isValidHtmlFilePath(const std::string& path) {
    size_t pos = path.rfind(".html");
    return pos != std::string::npos && pos == path.length() - 5;
}

// Function to validate 'error_page' parameters
bool validateErrorPageParams(const std::vector<std::string>& params) {
    if (params.empty()) {
        std::cerr << "No parameters provided for error_page." << std::endl;
        return false;
    }

    // The last parameter should be a file path
    std::string lastParam = params.back();
    if (!isValidHtmlFilePath(lastParam)) {
        std::cerr << "Invalid file path for error_page: " << lastParam << std::endl;
        return false;
    }

    // All other parameters should be valid HTTP status codes
    for (size_t i = 0; i < params.size() - 1; ++i) {
        if (!isValidHttpStatusCode(params[i])) {
            std::cerr << "Invalid HTTP status code for error_page: " << params[i] << std::endl;
            return false;
        }
    }
    std::cout << "All error_page parameters are valid." << std::endl;
    return true;
}

// AUTOINDEX
bool verifyAutoIndex(std::vector<std::string> params) {
    if (params.empty())
        return false;
    if (params.size() > 1)
        return false;
    std::string val = removeCharacter(params[0], ';');
    if ( val != "on" && val != "off" ) {
        //printErrs("error in auto index --> ");
        return false;
    }
    //printString("verify autoindex is ok with " + params[0]);
    return true;
}

bool verifyMethodesParam(std::vector<std::string> params) {
    if (params.empty())
        return false;

    for (size_t i = 0; i < params.size(); i++) {
        std::string val = removeCharacter(params[i], ';');
        if (val != "GET" && val != "POST" && val != "DELETE")
            return false;
    }
    return true;
}

// MODIFYER
bool isValidModifyer(std::string word) {
    if (word == "" || word.empty())
        return true;
    if (word == "~" || word == "^~" || word == "~*" || word == "~" || word == "~*" || word == "=" || word == "@") {
        return true;
    }
    printString("modifyer : [" + word + "] is not valid ");
    return false;
}

// CGI_PASS
// Helper function to trim spaces for accurate comparison in C++98 style
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos)
		return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Function to validate cgi_pass parameter
bool verifyCgiPass(const std::vector<std::string>& params) {
    for (size_t i = 0; i < params.size(); ++i) {
        std::string param = trim(params[i]);
        // Check if the parameter format is correct
        if (param.find("unix:") != 0) {
            std::cerr << "Invalid cgi_pass parameter: " << param << std::endl;
            return false;
        }
        // Further checking could involve verifying the path exists, but that is not possible here
    }
    std::cout << "All cgi_pass parameters are valid." << std::endl;
    return true;
}

// cgi_timeout
bool verifyCgi_timeout(std::vector<std::string> params) {
    try {

        if (params.empty() || params.size() > 1 )
            return false;

        char* endPtr = 0;
        long Val = std::strtol( params[0].c_str() , &endPtr, 10);

        if (endPtr == params[0].c_str() || *endPtr != '\0') {
            printErrs("Invalid parameter format in verifCgi_timeout: [" + params[0] + "]");
            return false;
        }

        if ( Val > INT_MAX || Val < INT_MIN || Val > 1000 || Val > 1000) {
            printErrs("( Seriously who such a big number ? ) : ERROR in verifCgi_timeout :: [" + intToString(Val)+"] max value of cgi_timeout is 1000");
            return false;
        }
    }
    catch(std::exception & e) {
        printErrs("Other type of error in verifCgi_timeout");
        return false;
    }
    return true;
}

// ONLY SERVER PARTS
bool nginx::isThereOnlyServParts( std::vector<std::string> _tokenizedNginxContent ) {
	
	bool 			inServer = false;
	int 			nbrOfBraces = 0;
	std::string 	word;
	
	if (_tokenizedNginxContent[0] != "server")
		return false;
	for (size_t i = 0; i < _tokenizedNginxContent.size(); i++) {
		word = _tokenizedNginxContent[i];
		if (word == "server" && nbrOfBraces == 0) {// if we are in a server
			inServer = true;
		}
		if ( word == "}" || word == "{" ) {
			if ( inServer == true ) {
				if ( word == "{")
					nbrOfBraces++;
				if ( word == "}")
					nbrOfBraces--;
				if (nbrOfBraces > 3 || nbrOfBraces < 0) {
					printErrs("Error on token ["+word+"] to many braces");
					return false;
				}
				if (nbrOfBraces == 0)
					inServer = false;
				continue;
			} else {
				printErrs("Error on token ["+word+"]");
				return false;
			}
		}
		if (nbrOfBraces == 0 && word != "server") {
			printErrs("Error on token ["+word+"]");
			return false;
		}
	}
	printString("return true in isThereOnlyServParts");
	return true;	
}

// LOCATION NAME 

bool startsWithSlash(const std::string& str) {

    // Vérifier si la chaîne n'est pas vide et si le premier caractère est un '/'
    if (str.empty() || (str[0] != '/' && str != "/")) {
        printErrs("ERROR str : " + str + " does not start with /");
        return false;
    }
    return true;
}

// Vérifie si le chemin de la location est valide
bool isValidLocationPath(const std::string& nameParam) {
    if (nameParam.empty()) {
        std::cerr << "Error: Location path is empty." << std::endl;
        return false;
    }

    if (!startsWithSlash(nameParam))
        return false;

    // Vérifie que le chemin commence par '/' ou contient des caractères permis pour une expression régulière
    if (nameParam[0] != '/' && !isalnum(nameParam[0]) && nameParam[0] != '\\') {
        std::cerr << "Error: Location path must start with '/' or alphanumeric characters. : ["<<nameParam<<"]" << std::endl;
        return false;
    }

    // Vérification supplémentaire pour tout caractère inattendu
    for (size_t i = 1; i < nameParam.length(); ++i) {
        if (!isalnum(nameParam[i]) && nameParam[i] != '/'
                                    && nameParam[i] != '.'
                                    && nameParam[i] != '-'
                                    && nameParam[i] != '_'
                                    && nameParam[i] != '~'
                                    && nameParam[i] != '$') {
            std::cerr << "Error: Invalid character '" << nameParam[i] << "' in location path." << std::endl;
            return false;
        }
    }

    return true;
}

// VERIF EACH LINE OF CONFIG FILE
bool isValidLineFormat(const std::string& line) {
	//printString("line : ["+line+"]");
    if (line.empty()) {
        std::cout << "Line is empty." << std::endl;
        return true;  // Lignes vides sont autorisées.
    }

    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;

    // Tokenize the line
    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) {
        std::cout << "Line only contains whitespace." << std::endl;
        return true;  // Lignes qui ne contiennent que des espaces sont aussi acceptées.
    }

    // Check the first valid token (should start with a letter, and can include _ or -)
    const std::string& firstToken = tokens.front();
    if (firstToken.size() == 1 && firstToken == "}")
		return true;
	if (!std::isalpha(firstToken[0])) {
        std::cout << "Invalid start of line, first significant character is not a letter: " << firstToken << std::endl;
        return false;
    }

    // Check the last valid token (should end with ';' or '{' or '}')
    const std::string& lastToken = tokens.back();
    char lastChar = lastToken[lastToken.size() - 1];
    if (lastChar != ';' && lastChar != '{' && lastChar != '}') {
        std::cout << "Invalid end of line, does not end with ';' or '{' or '}': " << lastToken << std::endl;
        return false;
    }

    return true;
}