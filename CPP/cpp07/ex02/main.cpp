#include <iostream>
#include "Array.hpp"
/*
#define MAX_VAL 750
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = i ;//= rand();
        numbers[i] = value;
        mirror[i] = value;
    }

    // SCOPE pour tester la copie
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    // Vérifie si les valeurs sont bien copiées
    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }

    // Test d'accès valide
    std::cout << "First element: " << numbers[0] << std::endl;
    std::cout << "Last element: " << numbers[MAX_VAL - 1] << std::endl;

    // Test d'accès hors limites (négatif)
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception for negative index: " << e.what() << '\n';
    }

    // Test d'accès hors limites (dépassant la taille)
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception for index out of range: " << e.what() << '\n';
    }

    // Modification des valeurs du tableau
    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }

    // Affichage de quelques nouvelles valeurs modifiées
    std::cout << "Modified first element: " << numbers[0] << std::endl;
    std::cout << "Modified last element: " << numbers[MAX_VAL - 1] << std::endl;
    // Test de la taille de l'Array
    std::cout << "Size of Array: " << numbers.size() << std::endl;
    if (numbers.size() != MAX_VAL) {
        std::cerr << "Size test failed!" << std::endl;
        return 1;
    }

    // Test d'accès à quelques éléments spécifiques
    const int testIndices[] = {0, MAX_VAL / 2, MAX_VAL - 1};
    for (int i = 0; i < 3; i++) {
        int index = testIndices[i];
        std::cout << "Element at index " << index << ": " << numbers[index] << std::endl;
    }

    delete [] mirror;
    return 0;
}
*/

#define MAX_VAL 750
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;//
    return 0;
}

/*
#include <iostream>
#include "Array.hpp"

int main() {
    try {
        // Test avec un Array d'entiers
        Array<int> intArray(5);
        for (unsigned int i = 0; i < intArray.size(); i++) {
            intArray[i] = i * i;
            std::cout << "intArray[" << i << "] = " << intArray[i] << std::endl;
        }

        // Test de copie
        Array<int> copiedArray = intArray;
        copiedArray[0] = 42;
        std::cout << "intArray[0] = " << intArray[0] << " (devrait être 0)" << std::endl;
        std::cout << "copiedArray[0] = " << copiedArray[0] << " (devrait être 42)" << std::endl;

        // Test d'accès hors limites
        std::cout << "Test d'accès hors limites:" << std::endl;
        std::cout << intArray[intArray.size()] << std::endl; // Devrait lancer une exception
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
*/