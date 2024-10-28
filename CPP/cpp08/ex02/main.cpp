#include "MutantStack.hpp"
#include <iostream>
#include <list>




int main() {
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    std::cout << mstack.top() << std::endl;
    mstack.pop();
    std::cout << mstack.size() << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    --it;
    while (it != ite) {
        std::cout << *it << std::endl;
        ++it;
    }

	std::cout << "\t---------Using list---------" << std::endl;
	{
	/*
	Si vous l’exécutez une première fois avec votre MutantStack, puis une seconde fois en
	remplaçant la MutantStack, par exemple par std::list, les deux résultats devront être
	identiques. Bien sûr, lorsque vous testez cet exemple avec un autre container, modifiez le
	code avec les fonctions membres correspondantes (push() peut devenir push_back()).
	*/
		std::list<int> mlist;

		// list 5 17
		mlist.push_back(5);
		mlist.push_back(17);
		// print back , so 17
		std::cout << mlist.back() << std::endl;

		//set 17 out
		mlist.pop_back();
		//print size so, == 1
		std::cout << mlist.size() << std::endl;
		
		//add those numbers to list , so 5, 3, 5, 737, 0
		mlist.push_back(3);
		mlist.push_back(5);
		mlist.push_back(737);
		mlist.push_back(0);

		//print space (\n)
		std::cout << std::endl;
		std::list<int>::iterator it = mlist.begin();
		std::list<int>::iterator ite = mlist.end();
		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
	}
	


    return 0;
}
