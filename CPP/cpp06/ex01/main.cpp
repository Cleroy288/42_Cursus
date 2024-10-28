// Cet exercice démontre la sérialisation et la désérialisation, des techniques pour convertir 
// des objets en un format pouvant être stocké ou transféré, et inversement. On apprend ici 
// à manipuler les pointeurs et les convertir en types entiers (uintptr_t) pour les opérations 
// de bas niveau ou la gestion de la mémoire. C'est une introduction fondamentale à des concepts 
// plus avancés de la programmation tels que la sérialisation de structures de données complexes
// pour le stockage ou la communication entre différents composants ou programmes.


#include "Serializer.hpp"
#include <iostream>

int main() {
    printS("Creating Data object with name John and value 42");
    Data original = {"John", 42};

    printS("Serializing the Data object to uintptr_t");
    uintptr_t raw = Serializer::serialize(&original);

    printS("Deserializing uintptr_t back to Data object pointer");
    Data *dPtr = Serializer::deserialize(raw);

    printS("Comparing original and deserialized Data");
    std::cout << "Original: " << original.name << ", " << original.value << std::endl;
    std::cout << "Deserialized: " << dPtr->name << ", " << dPtr->value << std::endl;
    return 0;
}
