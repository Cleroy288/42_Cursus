#include "nginx.hpp"

std::vector<std::string> tokenizeNginxContent( std::vector<std::string> _nginxContent) {

    std::vector<std::string> _tokenizedNgixContent;

	for (size_t i = 0; i < _nginxContent.size(); i++) {// tokenize content 
		
		std::istringstream 	iss(_nginxContent[i]);
		std::string 		token;
		
        while (iss >> token) {
			_tokenizedNgixContent.push_back(token);
		}
		
		//printString("<[ "+_nginxContent[i]+" ]>");// print content 
	}
    return _tokenizedNgixContent;
}

bool nginx::isFileContentValid() {

	std::vector<std::string> _tokenizedNgixContent = tokenizeNginxContent(_nginxContent);
	
    // rpint result 
	//for (size_t i = 0; i < _tokenizedNgixContent.size(); i++) {
	//	printString("[ "+_tokenizedNgixContent[i]+" ]");
	//}

    printString("============================================");
    std::cout << "===&&& |[ START PARAM VERIFICATION ]| &&&===" << std::endl;
    printString("============================================");

	if (!isThereOnlyServParts( _tokenizedNgixContent ))
		return false;
	
	if (!verifyGenParamInServ( _tokenizedNgixContent ))
        return false;

    if (!verifyLocationParams( _tokenizedNgixContent ))
        return false;

    printString("========================================");
    std::cout << "===&&& |[ ALL PARAMS ARE VALID ]| &&&===" << std::endl;
    printString("========================================");
	
    return true;
}