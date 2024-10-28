#ifndef ERRORANDPAGES_HPP
#define ERRORANDPAGES_HPP

#include "../../../includes/principal.hpp"

// structure in wich we set the error codes and the pages to wich we can find the files
typedef struct errorAndPages
{	
	// file way to the file to display
	std::string 	fileToRedirectTo;
	// codes to wich we display the given file
	std::vector<int> errorCodes;

} errorAndPages;


#endif