#ifndef PRINCIPAL_HPP
# define PRINCIPAL_HPP

/********************/
/**   LIB INCLUDES  */
/********************/

// Pour les entrées/sorties standards et les manipulations de chaînes
#include <iostream>
#include <cstring> // Pour strerror
#include <fstream> // Pour fstream
#include <cctype> // Pour isspace

// Pour la gestion des processus et des signaux
#include <unistd.h> // Pour execve, dup, dup2, pipe, fork, close, read, write, getpid, access
#include <sys/wait.h> // Pour waitpid
#include <signal.h> // Pour kill, signal
// Inclut l'en-tête pour std::vector
#include <vector>
// for std::isstringstream 
#include <sstream>

// Pour la programmation réseau
#include <sys/socket.h> // Pour socket, accept, listen, send, recv, bind, connect, getsockname, setsockopt
#include <netinet/in.h> // Pour htons, htonl, ntohs, ntohl
#include <arpa/inet.h> // Pour htonl, htons, ntohl, ntohs
#include <netdb.h> // Pour getaddrinfo, freeaddrinfo, getprotobyname

// Pour la gestion non bloquante des sockets
#include <sys/select.h> // Pour select
#include <poll.h> // Pour poll
//#include <sys/event.h> // Pour kqueue, kevent (Note: spécifique à BSD)
#include <cstdlib>// for exit

// Pour la manipulation de fichiers et de répertoires
#include <fcntl.h> // Pour fcntl
#include <sys/stat.h> // Pour stat
#include <dirent.h> // Pour opendir, readdir, closedir
#include <map>


/****************************/
/**     FUNCTION DEFS      **/
/****************************/

void			printString(const std::string &src);
void			printErrs(const std::string &src);
bool 			containsSemicolon(const std::string& input);
bool 			endsWithSemicolon( std::string& str);
std::string		extractFirstWord( const std::string &str);
std::string 	intToString(long long value);
std::string 	removeCharacter(const std::string& str, char charToRemove);
void 			printvec(std::vector<std::string> vec);
std::vector<std::string> removeCharFromVec( std::vector<std::string> Vec, char c);

// VERIFICATION FUCTIONS 
bool isInt(const std::string& str);
bool isIpAddress(const std::string& str);
bool verifyListenParam(std::vector<std::string> params);
bool isValidDomainSuffix(const std::string& domain);
bool containsOnlyValidCharacters(const std::string& domain);
bool validateServerName(const std::vector<std::string>& serverNames);
bool isValidIpAddress(const std::string& ipAddress);
bool validateHost(const std::vector<std::string>& params);
bool isValidRootPath(const std::string& path);
bool validateRoot(const std::vector<std::string>& params);
bool hasValidWebExtension(const std::string& filename);
bool validateIndexFiles(const std::vector<std::string>& params);
bool isValidSizeSpec(const std::string& sizeSpec);
bool validateClientMaxBodySize(const std::vector<std::string>& params);
bool isValidHttpStatusCode(const std::string& code);
bool isValidHtmlFilePath(const std::string& path);
bool validateErrorPageParams(const std::vector<std::string>& params);
bool verifyAutoIndex(std::vector<std::string> params);
bool verifyMethodesParam(std::vector<std::string> params);
bool isValidModifyer(std::string word);
bool verifyCgiPass(const std::vector<std::string>& params);
bool isValidLocationPath(const std::string& nameParam);
bool isValidLineFormat(const std::string& line);
bool verifyCgi_timeout(std::vector<std::string> params);


/*************************/
/**   PARSING FUNCTION  **/
/*************************/

bool	verifyConfigFile(const std::string &pathToConfigFile);

/*****************/
/**  STRUCTS     */
/*****************/

#include "../srcs/parsing/structs/errorAndPages.hpp"
#include "../srcs/parsing/structs/locationStruct.hpp"

/***************/
/**  CLASSES  **/
/***************/
// NOT INCLUDES ANNYMORE CUZ CAUSES ERRORS OF CIRCULAR INCLUSION 
//	#include "../srcs/exec/socket/socket.hpp" // file in wich the class socket is 
//	#include "../srcs/exec/client/client.hpp" // file in wich the class client is
//	#include "../srcs/parsing/server/server.hpp" // file in wich the class server is 
//	#include "../srcs/parsing/nginx/nginx.hpp" // file in wich the class nginx is 










#endif