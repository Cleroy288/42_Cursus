#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

/*
 * Le mot-clé 'virtual' en C++ est utilisé pour la création de méthodes pouvant être surchargées dans les classes dérivées.
 * Cela permet le polymorphisme, une caractéristique clé de la programmation orientée objet, permettant aux objets de se comporter différemment selon leur type spécifique.
 *
 * - Polymorphisme : Les méthodes virtuelles permettent aux classes dérivées de fournir des implémentations spécifiques, 
 *   tout en permettant au code de travailler avec des pointeurs ou des références à la classe de base.
 * - Destructeurs Virtuels : Essentiels pour assurer une destruction appropriée des objets dérivés lorsque manipulés via des pointeurs de la classe de base.
 * - Classes Abstraites : Une classe avec au moins une fonction virtuelle pure (marquée avec '= 0') est abstraite et ne peut pas être instanciée directement.
 *
 * L'usage de 'virtual' garantit que la fonction correcte est appelée selon le type réel de l'objet, même si celui-ci est référencé par un pointeur ou une référence de la classe de base.
 */


/*
 * Le spécificateur d'accès 'protected' en C++ est utilisé pour contrôler la visibilité des membres d'une classe (fonctions et variables).
 * Il offre un niveau d'accès intermédiaire entre 'public' et 'private'.
 *
 * - Accès dans la Classe : Les membres 'protected' sont accessibles depuis l'intérieur de la classe où ils sont déclarés.
 * - Accès dans les Classes Dérivées : Les membres 'protected' sont également accessibles dans les classes qui héritent de cette classe,
 *   permettant aux classes dérivées de manipuler ces membres.
 * - Inaccessibilité de l'Extérieur : Les membres 'protected' ne sont pas accessibles directement depuis l'extérieur de la classe,
 *   protégeant ainsi ces membres d'un accès non contrôlé tout en restant utiles pour l'héritage.
 *
 * L'utilisation de 'protected' est idéale pour les scénarios où vous souhaitez cacher certains membres de l'accès global,
 * mais les rendre disponibles pour les classes dérivées, facilitant ainsi la réutilisation et l'extension du code.
 */


int main() {
    // Test avec Animal, Dog, et Cat
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;

    i->makeSound();
    j->makeSound();
    meta->makeSound();

    delete i;
    delete j;
    delete meta;

    // Test avec WrongAnimal et WrongCat
    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    std::cout << wrongCat->getType() << " " << std::endl;

    std::cout<<"sound wrong animal"<<std::endl;
    wrongCat->makeSound();
    wrongMeta->makeSound();

    delete wrongCat;
    delete wrongMeta;



	const Animal* animal = new Animal();
	const Animal* dog = new Dog();
	const Animal* cat = new Cat();

	std::cout << std::endl;
	std::cout << "Dog->getType [" << dog->getType() << "] " << std::endl;
	std::cout << "Cat->getType [" << cat->getType() << "] " << std::endl;
	cat->makeSound(); //will output the cat sound! (not the Animal)
	dog->makeSound(); //will output the dog sound! (not the Animal)
	animal->makeSound(); //will output the animal sound

	std::cout << std::endl;
	const WrongAnimal* wrong_animal = new WrongAnimal();
	const WrongAnimal* wrong_cat = new WrongCat();

	std::cout << std::endl;
	wrong_cat->makeSound();
	wrong_animal->makeSound();

	std::cout << std::endl;
	delete animal;
	delete dog;
	delete cat;
	delete wrong_cat;
	delete wrong_animal;

    std::cout<<""<<std::endl;
    std::cout<<"test pdf"<<std::endl;

    const Animal* m = new Animal();
    const Animal* jj = new Dog();
    const Animal* ii = new Cat();
    std::cout << jj->getType() << " " << std::endl;
    std::cout << ii->getType() << " " << std::endl;
    ii->makeSound(); //will output the cat sound!
    jj->makeSound();
    m->makeSound();

    return 0;
}

