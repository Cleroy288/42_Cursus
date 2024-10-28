#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

/*

Lorsque vous déclarez une fonction membre (y compris un destructeur) comme virtual dans une classe de base,
vous permettez à cette fonction d'être "remplacée" dans les classes dérivées. Cela est crucial pour le polymorphisme.

Si le destructeur de Animal n'est pas virtual et que vous faites ceci :
Animal *animal = new Dog();
delete animal;
Seul le destructeur de Animal sera appelé, pas celui de Dog. Cela peut entraîner une fuite de mémoire,
car le Brain alloué dans Dog ne sera pas libéré.


*/

// Fonction pour tester la création et la destruction de base des animaux
void TestBasic() {
    // Créer un objet de chaque type
    const Animal* meta = new Animal();
    const Animal* dog = new Dog();
    const Animal* cat = new Cat();

    // Afficher le type de chaque animal
    std::cout << "\nTypes of Animals:" << std::endl;
    std::cout << "Dog: " << dog->getType() << std::endl;
    std::cout << "Cat: " << cat->getType() << std::endl;
    std::cout << "Animal: " << meta->getType() << std::endl;

    // Tester les sons produits par chaque animal
    std::cout << "\nTesting Sounds:" << std::endl;
    dog->makeSound();
    cat->makeSound();
    meta->makeSound();

    std::cout<<"Clenaing upt !"<<std::endl;
    // Nettoyer
    delete cat;
    delete dog;
    delete meta;
}

// Fonction pour tester un tableau d'animaux
void TestArray() {
    Animal* animals[20];

    // Remplir le tableau avec des chiens et des chats
    std::cout << "\nCreating Animals:" << std::endl;
    for (int i = 0; i < 20; i++) {
        animals[i] = (i % 2 == 0) ? static_cast<Animal*>(new Dog()) : static_cast<Animal*>(new Cat());
    }

    // Tester les sons
    std::cout << "\nAnimal Sounds:" << std::endl;
    for (int i = 0; i < 20; i++) {
        animals[i]->makeSound();
    }

    // Nettoyer
    std::cout << "\nDeleting Animals:" << std::endl;
    for (int i = 0; i < 20; i++) {
        delete animals[i];
    }
}

// Fonction principale
int main() {
    // Tester la création et la destruction de base
    std::cout << "Basic Test:" << std::endl;
    TestBasic();

    // Tester avec un tableau d'animaux
    std::cout << "\nArray Test:" << std::endl;
    TestArray();

    return 0;
}