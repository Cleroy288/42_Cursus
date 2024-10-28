#include "nginx.hpp"

std::vector<std::string> initValInParam(   ) {// create a vector with all the valid parametres we can have in general part of serv
    std::vector<std::string> _possibleParam;

    _possibleParam.push_back("listen");
    _possibleParam.push_back("server_name");
    _possibleParam.push_back("host");
    _possibleParam.push_back("root");
    _possibleParam.push_back("index");
    _possibleParam.push_back("client_max_body_size");
    _possibleParam.push_back("error_page");
    _possibleParam.push_back("autoindex");
    _possibleParam.push_back("methodes");
    _possibleParam.push_back("cgi_timeout");

    return _possibleParam;
}

bool nginx::handleBlockState(const std::string& word, bool& inServ, bool& inLoc) {
    if (word == "server" && !inLoc) {
        inServ = true;
        return true;
    }
    if (word == "location") {
        inLoc = true;
        return true;
    }
    if (word == "}") {
        if (inLoc) {
            inLoc = false;
        } else if (inServ) {
            inServ = false;
        }
        return true;
    }
    return false; // No state change
}

bool nginx::isGeneralServerParameter(const std::string& word, const std::vector<std::string>& possibleParams) {
    return std::find(possibleParams.begin(), possibleParams.end(), word) != possibleParams.end();
}

bool nginx::processServerParameters(std::string& word, bool inServ, bool inLoc, bool& setParam, std::string& currentParamName, std::vector<std::string>& currentParams, const std::vector<std::string>& possibleParam) {
    if (!inServ || inLoc)
        return true; // Only process if in server block and not in location block

    if (setParam) {
        if (containsSemicolon(word)) {//containsSemicolon(word)) {
            word = word.substr(0, word.size() - 1); // Remove semicolon for last parameter
            currentParams.push_back(word);
            if (!verifyParam(currentParamName, currentParams)) {// big function verify praram has it's own file
                printErrs("Invalid parameters for " + currentParamName);
                return false;
            }
            setParam = false; // Reset after processing
            currentParams.clear();
        } else {
            currentParams.push_back(word);
        }
        return true;
    }

    if (std::find(possibleParam.begin(), possibleParam.end(), word) != possibleParam.end()) {
        currentParamName = word;
        setParam = true;
        currentParams.clear();
        return true;
    }

    return true; // Continue processing
}

/** PRINCIPAL FUNCTION TO VERIFY DATA in gen part of serv */
bool nginx::verifyGenParamInServ(std::vector<std::string> _tokenizedNginxContent) {
    
    bool inServ = false;
	bool inLoc = false;
	bool setParam = false;
    
    std::string currentParamName;
    std::vector<std::string> currentParams;
    std::vector<std::string> _possibleParam = initValInParam();
    
	printString("=======================================================");
    std::cout << "===&&& |[ START All GENERAL parameters test . ]| &&&===" << std::endl;
    printString("=======================================================");

    for (size_t i = 0; i < _tokenizedNginxContent.size(); ++i) {
        std::string& word = _tokenizedNginxContent[i];

        if (!handleBlockState(word, inServ, inLoc)) {
            // If no block state change, process parameters
            if (!processServerParameters(word, inServ, inLoc, setParam, currentParamName, currentParams, _possibleParam)) {
                return false; // Stop if there is an error in parameter processing
            }
        }
    }
	
    printString("=====================================================");
    std::cout << "===&&& |[ All GENERAL parameters are valid. ]| &&&===" << std::endl;
    printString("=====================================================");
    
	return true; // All checks passed
}