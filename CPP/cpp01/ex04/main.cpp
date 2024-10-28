#include <iostream>
#include <fstream>
#include <string>

// Fonction principale du programme
int main(int argc, char **argv) {

	std::string src;
    std::string dst;
    std::string line;
	std::string outFileName;

	std::size_t pos;

    // Vérification du nombre d'arguments
    if (argc != 4) {
        std::cout << "Usage: ./replace <filename> <string1> <string2>" << std::endl;
        return 1;
    }

    // Tentative d'ouverture du fichier source
    std::ifstream infile(argv[1]);
    if (!infile) { // Si le fichier ne s'ouvre pas correctement
        std::cout << "Error: cannot open " << argv[1] << std::endl;
        return 1;
    }

    // Préparation du nom du fichier de sortie
    outFileName = std::string(argv[1]) + ".replace";

    // Tentative de création du fichier de sortie
    std::ofstream outfile(outFileName.c_str());
    if (!outfile) { // Si le fichier ne peut pas être créé
        std::cout << "Error: cannot create " << outFileName << std::endl;
        infile.close(); // Important : fermer infile avant de terminer le programme
        return 1;
    }

    // Définition des chaînes de recherche et de remplacement
    src = argv[2];
    dst = argv[3];

    // Lecture du fichier source ligne par ligne
    while (std::getline(infile, line)) {
        pos = 0;											//npos représente une constante qui représente une pos invalide dans la chaine.
        while ((pos = line.find(src, pos)) != std::string::npos)// Recherche de chaque occurrence de la chaîne 'src' dans 'line'
		{
            line.erase(pos, src.length());// Suppression de 'src' de la ligne
            line.insert(pos, dst);// Insertion de 'dst' à la position où 'src' se trouvait
            pos += dst.length();// Mise à jour de la position de recherche pour éviter une boucle sans fin
        }
        outfile << line << std::endl;// Écriture de la ligne modifiée dans le fichier de sortie
    }

    // Fermeture des fichiers pour libérer les ressources
    infile.close();
    outfile.close();

    return 0;
}
