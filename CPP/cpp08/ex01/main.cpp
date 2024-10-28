#include "Span.hpp"
#include <iostream>

int main() {
	
	{
	    Span sp1(5);
	    sp1.addNumber(6);
	    sp1.addNumber(3);
	    sp1.addNumber(17);
	    sp1.addNumber(9);
	    sp1.addNumber(11);

	    try {
	        std::cout << "Shortest Span: " << sp1.shortestSpan() << std::endl;
	        std::cout << "Longest Span: " << sp1.longestSpan() << std::endl;
	    } catch (std::exception& e) {
	        std::cerr << e.what() << std::endl;
	    }
	}

	std::cout<<"---------   other  -----------"<<std::endl;

	{
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}

	printS("------ new test --------");

	{
		Span sp(5);
	    std::cout << "Ajout de nombres à Span..." << std::endl;
	    sp.addNumber(6);
	    sp.addNumber(3);
	    sp.addNumber(17);
	    sp.addNumber(9);
	    sp.addNumber(11);

	    // Affichage du contenu de Span
	    std::cout << "Contenu de Span : " << std::endl;
	    std::cout << sp << std::endl;

	    // Test de shortestSpan et longestSpan
	    std::cout << "Le plus court span est : " << sp.shortestSpan() << std::endl;
	    std::cout << "Le plus long span est : " << sp.longestSpan() << std::endl;

	    // Test de la copie et de l'assignation
	    Span spCopy = sp; // Copie
	    Span spAssigned(10);
	    spAssigned = sp; // Assignation

	    // Test addRange
    	int moreNumbersArray[] = {20, 21, 22, 23, 24};
    	std::vector<int> moreNumbers(moreNumbersArray, moreNumbersArray + sizeof(moreNumbersArray) / sizeof(moreNumbersArray[0]));
    	std::cout << "Ajout d'une plage de nombres à Span..." << std::endl;
    	try {
    	    spAssigned.addRange(moreNumbers.begin(), moreNumbers.end());
    	} catch (const std::exception& e) {
    	    std::cerr << "Exception caught: " << e.what() << std::endl;
    	}


	    // Affichage du contenu de Span après addRange
	    std::cout << "Contenu de Span après addRange : " << std::endl;
	    std::cout << spAssigned << std::endl;

	}

    return 0;
}
