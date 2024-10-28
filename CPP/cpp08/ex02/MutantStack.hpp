#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque>

/**
 * 
 * c'est quoi une std::stack ?,  std::stack est un conteneur adaptateur en C++ qui fournit une structure de données de type pile
 * (LIFO - dernier entré, premier sorti). Il permet d'ajouter (push) et de retirer (pop) des éléments
 * uniquement depuis le haut de la pile, et de voir l'élément du haut (top) sans itérer sur tous les éléments.
 * 
 * Dans MutantStack, on étendez std::stack<T>,
 * en utilisant uniquement le premier paramètre template (type de l'élément), et le conteneur sous-jacent par défaut (std::deque<T>).
 * Le type du conteneur utilisé en interne pour stocker les éléments. Par défaut, c'est std::deque<T>,
*/

template <typename T>
class MutantStack : public std::stack<T> {
	private:

	public:
	    typedef typename std::stack<T>::container_type::iterator iterator;

	    MutantStack() : std::stack<T>() {}

	    MutantStack(const MutantStack& other) : std::stack<T>(other) {}
	    
		MutantStack& operator=(const MutantStack& other) {
	        std::stack<T>::operator=(other);
	        return *this;
	    }

	    ~MutantStack() {}

	    iterator begin() {
	        return this->c.begin();
	    }

	    iterator end() {
	        return this->c.end();
	    }


};

#endif
