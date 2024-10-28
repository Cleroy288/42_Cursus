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

/*
avec Makesound purement virtuelle les classe animal ne peuvent plus etre crée , car la classe Animale est abstraite

Une classe abstraite == au moins y avoir une fonction membre purement virtuelle
                            virtual void makeSound() const = 0; rend cette méthode purement virtuelle.


Pour quoi on ne peut plus crée un Animal ? 
    ==>     Cela signifie que vous ne pouvez pas faire new Animal() si Animal est une classe abstraite.
            La raison pour laquelle vous ne pouvez pas créer d'instance est que la classe contient des fonctions
            qui n'ont pas d'implémentation concrète, et donc, l'objet ne serait pas complet.

A quoi ça sert ?

==>     Cela force les classes dérivées à fournir leur propre implémentation de ces fonctions, garantissant ainsi que chaque sous-type a un
        comportement spécifique.
        Par exemple, pour Animal, cela signifie que chaque animal spécifique (comme Dog ou Cat) doit définir comment il fait un son (makeSound).


Pq ajouter virtual ne rend pas d'office un classe abstraite mais qu'il faut ajouter '= 0'

Pourquoi Ajouter Seulement virtual ne Rend Pas la Classe Abstraite?
==>         Virtual :

                Le mot-clé virtual signifie que la méthode peut être redéfinie dans une classe dérivée.
                Une méthode virtuelle peut avoir une implémentation dans la classe de base.
                Les classes dérivées peuvent, mais ne sont pas obligées, de fournir une nouvelle implémentation.

            Différence avec Purement Virtuel :

                Quand une méthode est purement virtuelle (= 0), elle ne possède pas d'implémentation dans la classe de base.
                Cela rend la méthode et, par extension, la classe incomplète tant qu'une classe dérivée ne fournit pas cette implémentation.

*/

// Fonction pour tester la création et la destruction de base des animaux
void TestBasic() {
    // Créer un objet de chaque type
    //const Animal* meta = new Animal();
    const Animal* dog = new Dog();
    const Animal* cat = new Cat();

    // Afficher le type de chaque animal
    std::cout << "\nTypes of Animals:" << std::endl;
    std::cout << "Dog: " << dog->getType() << std::endl;
    std::cout << "Cat: " << cat->getType() << std::endl;
    //std::cout << "Animal: " << meta->getType() << std::endl;

    // Tester les sons produits par chaque animal
    std::cout << "\nTesting Sounds:" << std::endl;
    dog->makeSound();
    cat->makeSound();
    //meta->makeSound();

    std::cout<<"Clenaing upt !"<<std::endl;
    // Nettoyer
    delete cat;
    delete dog;
    //delete meta;
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