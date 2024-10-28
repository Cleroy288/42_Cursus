#ifndef EASYFIND
#define EASYFIND

#include <iostream>
#include <algorithm>
#include <vector>
#include <exception>

// Exception personnalisée pour indiquer que l'élément n'a pas été trouvé
class NotFoundException : public std::exception {
public:
    const char* what() const throw() {
        return "Element not found in the container";
    }
};

// Fonction template easyfind
template <typename T>
int easyfind(T& container, int toFind) {
    typename T::iterator it = std::find(container.begin(), container.end(), toFind);
    if (it == container.end()) {
        throw NotFoundException();  // Lancer une exception si l'élément n'est pas trouvé
    }
    return std::distance(container.begin(), it);  // Renvoyer l'indice de l'élément
}

#endif