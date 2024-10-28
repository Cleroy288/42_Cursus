#include "includes/principal.hpp"
#include "srcs/exec/client/client.hpp"
#include "srcs/exec/socket/socket.hpp"

#include "srcs/parsing/nginx/nginx.hpp"
#include "srcs/parsing/server/server.hpp"

/** TODO 
 * 
 * 1 :: add verification in verifyConfigFile to see if the files dispalye
 * in he nginx file are accessible or not and if we have acces to the directory 
 * 
 * 2 :: CGI manage ervything to do with CGI ( routes, modify our config file, use fast cgi )
 * 
 * 3 :: create adapted responses for client, and manage request , we need to be able to manage Chrome, firfox, safari, brave as webbrowser
 * 
**/

// function to parse the nginx file in default nginx constructor and the to start all the servers 
bool	startParsingAndExecution( std::string pathToConfigFile ) {

	try {
		nginx nginxFile( pathToConfigFile );// make nginx file
		if (!nginxFile.startAllServers())// execute / start all servers
		{
			printErrs("ERROR from startAllServers");
			return false;
		}
		printErrs("Sopping server in main");
		return true; // return true cuz everything appended well 
	}
	catch( std::exception &e ) {
		printErrs(e.what());// print the error
		return false;
	}
	return false;// return false cuz true was not send back
}

int main(int argc, char **argv) {

	//std::string configFile;

	// conditions for config file
	std::string configFile = (argc > 1) ? argv[1] : "./ConfigFile/configfile";
	/*if (argc == 2) {
		configFile = argv[1];
	} else if (argc == 1) {
		configFile = "./ConfigFile/configfile";
	}*/
	// verify congfig file
	if (!verifyConfigFile(configFile))
		return 1;
	
	if (!startParsingAndExecution(configFile)) {
		printString("Error in startParsingAndExecution , program is stopped");
		return 1;
	}
	return 0;
}