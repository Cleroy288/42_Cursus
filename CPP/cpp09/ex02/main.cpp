#include "PmergeMe.hpp"

template<typename Container>
void printBefore(const Container& elements) {
    std::cout << "Before: ";
    for (typename Container::const_iterator it = elements.begin(); it != elements.end(); ++it) {
        if (it != elements.begin()) std::cout << " ";
        std::cout << *it;
    }
    std::cout << std::endl;
}

template<typename Container>
void printAfter(const Container& elements) {
    std::cout << "After: ";
    for (typename Container::const_iterator it = elements.begin(); it != elements.end(); ++it) {
        if (it != elements.begin()) std::cout << " ";
        std::cout << *it;
    }
    std::cout << std::endl;
}

template<typename Iterator>
void mergeAndSort(Iterator begin, Iterator middle, Iterator end) {
    // type of value inside of conteners
    typedef typename std::iterator_traits<Iterator>::value_type ValueType;
    // création de conteners gauche et droite 
    std::vector<ValueType> leftHalf(begin, middle);
    std::vector<ValueType> rightHalf(middle, end);

    // use explicite itérator to go inside of container 
    typename std::vector<ValueType>::iterator leftIter = leftHalf.begin();
    typename std::vector<ValueType>::iterator rightIter = rightHalf.begin();
    // pointer on original container elementsCopy
    Iterator targetIter = begin;

    // sorte 
    while (leftIter != leftHalf.end() && rightIter != rightHalf.end()) {
        if (*leftIter <= *rightIter) {
            *targetIter++ = *leftIter++;
        }
		else {
            *targetIter++ = *rightIter++;
        }
    }

    // merge si un coté à encore des éléments
    while (leftIter != leftHalf.end()) {
        *targetIter++ = *leftIter++;
    }

    while (rightIter != rightHalf.end()) {
        *targetIter++ = *rightIter++;
    }
}

// Exemple de correction pour 'auto length = std::distance(begin, end);'
template<typename Iterator>
void sortElem(Iterator begin, Iterator end) {
    Iterator middle;

    // nombre d'éléments dans le conteners
    typename std::iterator_traits<Iterator>::difference_type length = std::distance(begin, end);

    if (length > 1) {
        middle = std::next(begin, length / 2);
        sortElem(begin, middle);// on sépare sur la gauche 
        sortElem(middle, end);// on sépare sur la droite 
        mergeAndSort(begin, middle, end); // on trie et merge
    }
}


template<typename Container>
void sort(Container &elements) {
    // Appel de sortElem avec les itérateurs correspondant au début et à la fin du conteneur
    sortElem(elements.begin(), elements.end());
}

// us ==> Une microseconde (us) équivaut à 0,000 001 seconde (1/1 000 000 de seconde).
template<typename Container>
void sortAndMeasureTime(const Container &elements, const std::string &containerType) {
    Container elementsCopy;
    clock_t start;
    clock_t end;
    double duration;

    elementsCopy = elements; // Créer une copie pour ne pas modifier l'original
    printBefore(elementsCopy);
    start = clock();
    
    sort(elementsCopy);// sort
    
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC * 1000000; // Converti en microsecondes
    printAfter(elementsCopy);

    std::cout << "Time to process a range of " << elementsCopy.size() << " elements with " << containerType << ": " << duration << " us in microseconds" << std::endl;
}

bool execute(const std::deque<std::string> &args) {
    // create containers
    std::vector<long> elements; 
    std::list<long> elements2;

    // Remplir les conteneurs avec les valeurs fournies
    for (unsigned long i = 0; i < args.size(); i++) {
        long value = std::stoi(args[i]);
        elements.push_back(value);
        elements2.push_back(value);
    }

    // Utiliser la fonction pour trier et mesurer le temps pour std::vector
    sortAndMeasureTime(elements, "std::vector");

    // Utiliser la fonction pour trier et mesurer le temps pour std::list
    sortAndMeasureTime(elements2, "std::list");

    return true;
}

int 	main(int argc, char **argv) {
	std::deque<std::string> args;

    if (argc <= 3001) {
	    if (argc > 1) {
	    	for(int i = 1; argv[i] && i < argc; i++) {
	    		args.push_back(argv[i]);
	    	}
	    	if (!parsing(args)) {
	    		PrintErr("Parsing error, please verify your arguments");
	    		return 1;
	    	}
	    	execute(args);
	    }
    }
	return 0;
}