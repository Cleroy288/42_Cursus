#include "../../includes/principal.hpp"

void	printString(const std::string &src) {
	std::cout<<src<<std::endl;
}

void	printErrs(const std::string &src) {
	std::cerr<<src<<std::endl;
}

std::string extractFirstWord( const std::string &str) {

	size_t firstSpace = str.find(' ');// find first space 

	if (firstSpace == std::string::npos) {
		return str; // return whoe str if no space is found 
	} else {
		return str.substr(0, firstSpace);// return first word till space 
	}
}

std::string intToString(long long  value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

std::string removeCharacter(const std::string& str, char charToRemove) {
    std::string result;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] != charToRemove) {
            result += str[i];
        }
    }
    return result;
}

bool endsWithSemicolon( std::string& str) {
    if (!str.empty() && str[str.length() - 1] == ';') {
        return true;
    }
    return false;
}

bool containsSemicolon(const std::string& input) {
    // Utilisation de find pour chercher le caractère ';'
    size_t pos = input.find(';');
    if (pos != std::string::npos) {
        // Si find() ne retourne pas npos, cela signifie que ';' est trouvé dans la chaîne
        return true;
    }
    return false;
}

void printvec(std::vector<std::string> vec) {
	printString(":::: PRINTVEC :::: ");
	for (size_t i = 0; i < vec.size(); i++) {
		printString("["+vec[i]+"]");
	}
}

std::vector<std::string> removeCharFromVec( std::vector<std::string> Vec, char c) {
    std::vector<std::string> ret = Vec;
    for (size_t k = 0; k < ret.size(); k++) {
		ret[k] = removeCharacter(ret[k], c);
	}
	return ret;//_locationData[i]._nameAndParam[j].second;
}