#include "BitcoinExchange.hpp"

/*
 * Fonction isValidPositiveNumber :
 * Cette fonction vérifie si une chaîne de caractères représente un nombre positif, 
 * qu'il soit entier ou flottant. Elle est utilisée pour valider la partie "valeur" 
 * des lignes formatées "date | valeur" dans le fichier d'entrée.
 * 
 * La fonction retourne 'true' si la chaîne peut être convertie en un nombre positif 
 * et que la chaîne ne contient aucun caractère supplémentaire après le nombre. 
 * Cela assure que la valeur est strictement numérique et positive.
 * 
 * Fonction validateLineFormat :
 * Cette fonction vérifie le format global de chaque ligne dans le fichier d'entrée. 
 * Elle s'assure que chaque ligne suit le format "date | valeur", où la date doit 
 * être au format "AAAA-MM-JJ" et la valeur doit être un nombre positif (entier ou flottant).
 * La validation de la date vérifie la présence de trois composantes numériques séparées 
 * par des tirets, et la validation de la valeur utilise isValidPositiveNumber pour 
 * s'assurer que la valeur est positive et numérique.
 * 
 * En cas de format invalide, la fonction retourne 'false', permettant ainsi au code appelant 
 * de gérer l'erreur, par exemple en affichant un message d'erreur approprié.
 */

// Fonction pour vérifier si une chaîne est un nombre entier positif
bool isPositiveInteger(const std::string &str) {
    if (str.empty())
		return false;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        if (!std::isdigit(*it))
			return false;
    }
    return true;
}

// Fonction pour vérifier si une chaîne représente un nombre positif (entier ou flottant)
bool isValidPositiveNumber(const std::string &str) {
    if (str.empty())
		return false;
    std::istringstream iss(str);
    double num;
    iss >> num;
    if (!iss || !iss.eof() || num < 0) {
        return false; // Échoue si la lecture échoue, si la chaîne n'est pas consommée entièrement, ou si le nombre est négatif
    }
    return true;
}

// Fonction pour valider le format de la ligne
bool validateLineFormat(const std::string &line) {
	size_t 			delimiterPos;
	std::string 	datePart; 
	std::string 	valuePart;
    std::string 	year, month, day;

    delimiterPos = line.find('|');
    if (delimiterPos == std::string::npos || delimiterPos == 0 || delimiterPos == line.length() - 1) {
        return false; // Absence de '|' ou '|' en position initiale ou finale
    }

    datePart = line.substr(0, delimiterPos);
    valuePart = line.substr(delimiterPos + 1);

    // Suppression des espaces autour du '|'
    datePart.erase(remove(datePart.begin(), datePart.end(), ' '), datePart.end());
    valuePart.erase(remove(valuePart.begin(), valuePart.end(), ' '), valuePart.end());

    // Validation de la partie date
    std::istringstream dateStream(datePart);
    if (!getline(dateStream, year, '-') || year.length() != 4 || !isPositiveInteger(year) ||
        !getline(dateStream, month, '-') || month.length() != 2 || !isPositiveInteger(month) ||
        !getline(dateStream, day) || day.length() != 2 || !isPositiveInteger(day)) {
        return false; // Format de date incorrect
    }

    // Validation de la partie valeur avec la nouvelle fonction
    if (!isValidPositiveNumber(valuePart)) {
        return false; // La partie valeur n'est pas un nombre positif valide
    }

    return true; // La ligne est valide
}