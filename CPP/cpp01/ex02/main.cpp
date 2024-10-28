#include <iostream>
#include <string>
//pointeur == pointe vers une zone mémoire
//refernce == alias les 2 sont les memes 
int main() {
    // La chaîne originale
    std::string str = "HI THIS IS BRAIN";

    // Le pointeur et la référence à la chaîne
    std::string* stringPTR = &str;
    std::string& stringREF = str;

    // Afficher les adresses de la chaîne en mémoire == les memes 
    std::cout << "Address of the original string: " << &str << std::endl;
    std::cout << "Address stored in stringPTR: " << stringPTR << std::endl;
    std::cout << "Address stored in stringREF: " << &stringREF << std::endl;

    // Séparateur pour une meilleure lisibilité
    std::cout << "--------------------------------" << std::endl;

    // Afficher la valeur de la chaîne
    std::cout << "Value of the original string: " << str << std::endl;
    std::cout << "Value pointed by stringPTR: " << *stringPTR << std::endl;
    std::cout << "Value pointed by stringREF: " << stringREF << std::endl;

    return 0;
}
