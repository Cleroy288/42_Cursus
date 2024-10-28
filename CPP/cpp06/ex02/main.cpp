#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <iostream>

Base* generate(void) {
    switch (rand() % 3) {
    case 0: return new A();
    case 1: return new B();
    case 2: return new C();
    }
    return nullptr;  // Should never be reached
}

// identify(Base* p) : Identifie le type réel de l'objet pointé par 'p'.
// Utilise dynamic_cast pour tenter une conversion vers chaque type dérivé possible.
// Si la conversion est réussie, imprime le type de l'objet.

void identify(Base* p) {
    if (dynamic_cast<A*>(p))
		std::cout << "A";
    else if (dynamic_cast<B*>(p))
		std::cout << "B";
    else if (dynamic_cast<C*>(p))
		std::cout << "C";
}

// identify(Base& p) : Identifie le type réel de l'objet référencé par 'p'.
// Utilise une approche similaire à la fonction précédente mais avec des références et un bloc try-catch,
// offrant une sécurité accrue en évitant les pointeurs nuls.

void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
		std::cout << "A";
    } catch (...) {}
    try {
        (void)dynamic_cast<B&>(p);
		std::cout << "B";
    } catch (...) {}
    try {
        (void)dynamic_cast<C&>(p);
		std::cout << "C";
    } catch (...) {}
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    Base* obj = generate();
    identify(obj);
    identify(*obj);
    delete obj;
    return 0;
}
