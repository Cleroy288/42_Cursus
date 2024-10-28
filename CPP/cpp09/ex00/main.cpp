#include "BitcoinExchange.hpp"

// print à string and uses cout our cerr in function of one or two
void	printString(const std::string &toPrint, int oneOrTwo) {
	if (oneOrTwo == 1)
		std::cout<<toPrint<<std::endl;
	else
		std::cerr<<toPrint<<std::endl;
}

// Vérifie l'accès au fichier d'entrée
bool accessToInputFile(const std::string &inFile) {
    std::ifstream inputFile;
    inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        inputFile.open(inFile);
        // Autres opérations avec le fichier si nécessaire
        inputFile.close();
		//printString("Acces to inputfile granted", 1);
    } catch (const std::ifstream::failure& e) {
        printString("Error: could not open file " + inFile + " - " + e.what(), 2);
        return false;
    }
    return true;
}

bool hasCsvExtension(const std::string &filename) {
	std::string extension1;
	std::string extension2;
	// see if file has .csv from end
	if (filename.length() > 4) {
		extension1 = filename.substr(filename.length() - 4);
	}
	// see if file has .csv from start
	std::size_t dotPosition = filename.find_last_of(".");
	if (dotPosition != std::string::npos) {
		extension2 = filename.substr(dotPosition);
	}
	if (extension1 == ".csv" && extension2 == ".csv") {
		//printString("Database hase the right .csv extension", 1);
		return true;
	}
	printString("Database hasen't the right .csv extension", 1);
	return false;
}

bool accesToDataBaseFile(const std::string &dbFile) {
	std::ifstream dbInputfile;
	dbInputfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		dbInputfile.open(dbFile);
		dbInputfile.close();
		//printString("Acces to data base granted", 1);
	} catch(const std::ifstream::failure &e) {
		printString("Error: could not open data base file " + dbFile + " - " + e.what(),  2);
		return false;
	}
	return true;
}

// Définit une fonction pour charger les données depuis un fichier dans une map.
std::map<std::string, double> loadDatabase(const std::string& dbFile) {
    // Crée une map vide pour stocker les données de la base de données.
    std::map<std::string, double> database;
    
    // Tente d'ouvrir le fichier de base de données spécifié.
    std::ifstream db(dbFile.c_str());
    // Vérifie si le fichier a été ouvert avec succès.
    if (!db) {
        // Affiche un message d'erreur si le fichier ne peut pas être ouvert.
        std::cerr << "Error: could not open database file " << dbFile << std::endl;
        // Retourne la map vide si le fichier ne peut pas être ouvert.
        return database;
    }
    
    // Déclare une variable pour stocker chaque ligne lue du fichier.
    std::string line;
    // Lit le fichier ligne par ligne.
    while (getline(db, line)) {
        // Utilise un istringstream pour traiter la ligne lue.
        std::istringstream iss(line);
        // Déclare des variables pour stocker la date et la valeur extraite de la ligne.
        std::string date;
        double btcValue;
        // Tente d'extraire la date et la valeur de la ligne.
        // La date est lue jusqu'à la virgule, et la valeur est lue après la virgule.
        if (getline(iss, date, ',') && iss >> btcValue) {
            // Si la date et la valeur sont lues avec succès, les ajoute à la map.
            database[date] = btcValue;
        }
    }
    
    // Ferme le fichier une fois toutes les lignes lues et traitées.
    db.close();
    // Retourne la map remplie avec les données de la base de données.
    return database;
}


// Fonction pour trouver la valeur pour la date donnée ou la plus proche vers le bas.
// Retourne true si une date correspondante a été trouvée, false sinon.
// La valeur trouvée est retournée via le paramètre 'foundValue'.
bool findClosestDateAndValue(const std::string &targetDate, const std::map<std::string, double> &database, double &foundValue) {
    std::string closestDate = "";
    double closestValue = 0.0;
    bool found = false;

    for (std::map<std::string, double>::const_iterator it = database.begin(); it != database.end(); ++it) {
        if (it->first <= targetDate) {
            closestDate = it->first;
            closestValue = it->second;
            found = true; // Une date correspondante a été trouvée.
        } else {
            // Dès qu'une date dépasse la date cible, arrête la boucle.
            break;
        }
    }

    if (found) {
        foundValue = closestValue;
    }
    return found;
}

bool findDateInDbAndCalcVal(const std::string &dateAndAmount, const std::map<std::string, double> &database) {
    double quantity;
    double value;
	double finalValue;

    size_t delimiterPos = dateAndAmount.find('|');
    if (delimiterPos == std::string::npos) {
        std::cerr << "Invalid format: " << dateAndAmount << std::endl;
        return false;
    }

    std::string date = dateAndAmount.substr(0, delimiterPos);
    std::string amountStr = dateAndAmount.substr(delimiterPos + 1);
    date.erase(remove(date.begin(), date.end(), ' '), date.end());
    amountStr.erase(remove(amountStr.begin(), amountStr.end(), ' '), amountStr.end());

    std::istringstream(amountStr) >> quantity; // Conversion de la quantité en double
	if (quantity < 0) {
    	printString("Error: not a positive number.", 2);
    	return false;
	}
	if (quantity > 20000000) {
		printString("Error: too large number .", 2);
    	return false;
	}

    if (findClosestDateAndValue(date, database, value)) {
        // Calculer la valeur finale
        finalValue = quantity * value;
        
        // Convertir la valeur finale en std::string pour l'affichage
        std::ostringstream oss;
        oss << finalValue;
        std::string finalValueStr = oss.str();

        // Afficher le résultat
        printString(date + " => " + amountStr + " = " + finalValueStr, 1);
    } else {
        printString("No matching or lower date found in database for: " + date, 2);
    }

    return true;
}


void processBitcoinData(const std::string &inputFile, const std::string &dbFile) {
	// Charger la base de données
    std::map<std::string, double> database = loadDatabase(dbFile);

    // Ouvrir le fichier d'entrée
    std::ifstream input(inputFile.c_str());

    if (!input) {
        printString("Error: could not open input file " + inputFile, 2);
        return;
    }

    std::string line;
    getline(input, line); // Lire et ignorer l'en-tête (première ligne)

    // Lire chaque ligne suivante du fichier
    while (getline(input, line)) {
		if (!validateLineFormat(line)) {
        	printString("Error line, wrong format: " + line, 2);
        	continue; 
    	}
		findDateInDbAndCalcVal(line, database);
    }
    // Fermer le fichier
    input.close();
}


int main(int argc, char** argv) {
	std::string dbfile = "../cpp_09/data.csv";
	
	if (argc == 2) {
		try {
			std::string inFile = argv[1];
			if (!accessToInputFile(inFile) || !accesToDataBaseFile(dbfile) || !hasCsvExtension(dbfile))
			{// fail
				//exception is printed
				return 1;
			}
			//succes
            processBitcoinData(inFile, dbfile);

		} catch(const std::exception &e) {
			printString("Exception " + std::string(e.what()), 2);
			return 1;
		}
	} else {
		printString("Usage: [program] [input file]", 2);
        return 1;
	}
    return 0;
}
