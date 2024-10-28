#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>
#include <algorithm>
#include <iostream>
#include <limits>

class Span {
private:
    std::vector<int> numbers;
    unsigned int max_size;

public:
    Span(unsigned int N);
	Span(const Span &src);
	~Span();

	Span &operator=(const Span &src);



    void addNumber(int number);
    int shortestSpan() const;
    int longestSpan() const;

    //template <typename Iterator>
    //void addRange(Iterator begin, Iterator end);


	void printContend() const {
	    for (size_t i = 0; i < this->numbers.size(); i++) {
	        std::cout << this->numbers[i] << std::endl;
	    }
	}


    template <typename Iterator>
    void addRange(Iterator begin, Iterator end) {
        while (begin != end) {
            addNumber(*begin);
            ++begin;
        }
    }


};

std::ostream &operator<<(std::ostream &out, const Span &span);
void	printS(std::string s);

#endif
