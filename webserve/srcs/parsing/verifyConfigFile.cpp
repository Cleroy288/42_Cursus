#include "../../includes/principal.hpp"

static bool	verifyAccesToFile(const std::string &pathToConfigFile) {
	// convert st::string to const char * str cuz acces doesnt accept std::string
	const char *str = pathToConfigFile.c_str();
	// verify acces to file if read rule is ok
	if (access(str, R_OK) != 0) {
		printErrs("Error file " + pathToConfigFile + " not found or no read acces");
		return false;
	}
		
	return true;
}

static bool	verifyIfFileCanBeOpened(std::ifstream &configFile, const std::string &pathToConfigFile) {
	// verify if we can open the file
	if (!configFile.is_open()) {
		printErrs("Error cannot open file : " + pathToConfigFile);
		return false;
	}
	return true;
}

static bool	verifyIfFileIsNotEmpty(std::ifstream &configFile) {//const std::string &pathToConfigFile) {
	//std::ifstream 	configFile(pathToConfigFile);
	std::string		line;
	int				oneLineNotEmpty;

	oneLineNotEmpty = 0;
	// read the file line by line
	while (std::getline(configFile, line)) {
		
		//printString("line we got : ["+ line + "]"); // see what is the recieved file
		// remove all spaces and other stuff to verify if file is not filled with empty spaces
		line.erase(0, line.find_first_not_of(" \t\n\v\f\r")); // Supprime les espaces blancs au début
        line.erase(line.find_last_not_of(" \t\n\v\f\r") + 1); // Supprime les espaces blancs à la fin

		// increment oneLineNotEmpty when one line is not empty 
		if (!line.empty() )
			oneLineNotEmpty ++;
	}
	// default destructor of ifstream closes file but we are going to do it explicitly for lisibility purpuse
	configFile.close();

	// if at least one time is not empty return true
	if (oneLineNotEmpty != 0)
		return true;
	// return false wich mean every line found in file was empty
	printErrs("Erorr : an empty file has been given");
	return false;
}
// only function in .hpp
bool	verifyConfigFile(const std::string &pathToConfigFile) {

	std::ifstream 	configFile(pathToConfigFile.c_str());

	if (!verifyAccesToFile(pathToConfigFile))
		return false;
	if (!verifyIfFileCanBeOpened(configFile, pathToConfigFile))
		return false;
	if (!verifyIfFileIsNotEmpty(configFile))
		return false;
	
	return true;
}