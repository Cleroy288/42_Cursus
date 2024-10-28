#include "Span.hpp"


//	constructor && destructor
Span::Span(unsigned int N) : max_size(N) {
	printS("Default constructor called");
}

Span::Span(const Span &src) : numbers(src.numbers), max_size(src.max_size) {
	printS("Copy constructor called");
}

Span::~Span() {
	printS("Destructor called");
}

//   overload
Span &Span::operator=(const Span &src) {
	printS("Assignation operator overload called");
    if (this != &src) {  // Vérifier si l'objet source est différent de l'objet actuel
        this->numbers = src.numbers;
        this->max_size = src.max_size;
    }
    return *this;  // Retourner une référence à l'objet actuel
}

std::ostream &operator<<(std::ostream &out, const Span &span) {
    span.printContend();
    return out;
}

//asked functions
void Span::addNumber(int number) {
    if (numbers.size() >= max_size) {
        throw std::length_error("Span is already full.");
    }
    numbers.push_back(number);
}

int Span::shortestSpan() const {
    if (numbers.size() < 2) {
        throw std::logic_error("Not enough elements to find a span.");
    }

    std::vector<int> sorted(numbers);
    std::sort(sorted.begin(), sorted.end());

    int min_span = std::numeric_limits<int>::max();
    for (size_t i = 0; i < sorted.size() - 1; ++i) {
        int span = sorted[i + 1] - sorted[i];
        if (span < min_span) {
            min_span = span;
        }
    }
    return min_span;
}

int Span::longestSpan() const {
    if (numbers.size() < 2) {
        throw std::logic_error("Not enough elements to find a span.");
    }

    int min_element = *std::min_element(numbers.begin(), numbers.end());
    int max_element = *std::max_element(numbers.begin(), numbers.end());
    return max_element - min_element;
}
/*
template <typename Iterator>
void Span::addRange(Iterator begin, Iterator end) {
    while (begin != end) {
        addNumber(*begin);
        ++begin;
    }
}*/

void	printS(std::string s) {std::cout<<s<<std::endl;}