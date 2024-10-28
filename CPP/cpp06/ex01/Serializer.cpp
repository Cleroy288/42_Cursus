#include "Serializer.hpp"

void printS(std::string s) {
    std::cout << s << std::endl;
}

Serializer::Serializer() {
	printS("Serializer Constructor Called");
}

Serializer::Serializer(const Serializer &) {
	printS("Serializer Copy Constructor Called");
}

Serializer::~Serializer() {
	printS("Serializer Destructor Called");
}

Serializer &Serializer::operator=(const Serializer &) {
	printS("Serializer Assignment Operator Called");
	return *this;
}

// Convertit un pointeur de Data en un entier de type uintptr_t.
// Cette opération est souvent utilisée pour pouvoir manipuler ou stocker des pointeurs dans des formats non pointeurs.
uintptr_t Serializer::serialize(Data* ptr) {
    printS("serialize Called");
    return reinterpret_cast<uintptr_t>(ptr);
}

// Convertit un entier de type uintptr_t en pointeur de Data.
// Cette opération est utilisée pour récupérer le pointeur original après qu'il ait été transformé en un entier par la méthode serialize.
Data* Serializer::deserialize(uintptr_t raw) {
    printS("deserialize Called");
    return reinterpret_cast<Data*>(raw);
}
