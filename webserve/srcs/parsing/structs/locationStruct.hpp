#ifndef LOCATIONSTRUCT_HPP
#define LOCATIONSTRUCT_HPP

#include "../../../includes/principal.hpp"

typedef struct locationData {

	// location of the url " /... "
	std::string _location;

	// the name of the paramètres we have in the location 
	std::vector<std::string> _params;

	// the number of params we have
	int		_nbrOfParam;

	// extra modifyer
	std::string _modifyer;

	// TO DO redirections 
	//std::string _redirection;

	// in wich in can stock the name of the param and its parameter , like : 
	// client_max_body_size 8M;   &&  { [ client_max_body_size ] - [ 8M, 7M, etc... ] }
	// _METHODS are also in it 
	// _REDIRECTION are in here to : name=redirection, params="files" 
	std::vector< std::pair< std::string, std::vector<std::string> > > _nameAndParam;


} locationData;

/*
	// location 

	// pas location 
		function qui pemret d'aller chercher des data dans le fichier de server sans aller dans location et renvoyer ces info's 
		--> ex : error_pages : 404 

	// renvoi les fichier de code d'erreur sur base du location dans le quel ils sont 
	// getErrorAndPAges( int errorCode, std::string locationName ) {

	}

	// pareil mais pour la partie génaral 
	// getErrorAndPAges( int errorCode ) {
		return file;
	}


	// localhost:8080/api/index.html || localhost:8080/qlq.php fonction qui renvoi le nom de la location a utiliser si on y fait référrence dans une requete
	std::string getNameOfLocationBAsedOnURL ( std::string& URL )
	// fonction qui renvoi le nom de une location trouvé dans l'URL

*/

#endif