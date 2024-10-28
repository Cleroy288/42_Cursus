

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>
#include <iostream>

template <typename T>
class Array {
private:
    T* elements;
    unsigned int length;

public:
    Array() : elements(new T[0]), length(0) {}

    Array(unsigned int n) : elements(new T[n]()), length(n) {}

    Array(const Array& other) : elements(new T[other.length]), length(other.length) {
        for (unsigned int i = 0; i < length; i++) {
            elements[i] = other.elements[i];
        }
    }

    ~Array() {
        delete[] elements;
	}

    Array& operator=(const Array& other) {
        if (this != &other) {
            T* newElements = new T[other.length];
            for (unsigned int i = 0; i < other.length; i++) {
                newElements[i] = other.elements[i];
            }
            delete[] elements;
            elements = newElements;
            length = other.length;
        }
        return *this;
    }

    T& operator[](unsigned int index) {
        if (index >= length) {
				throw IndexOutOfBoundsException();
			}
				return elements[index];
	}
	unsigned int size() const {
    	return length;
	}

	class IndexOutOfBoundsException: public std::exception {
	public:
    	virtual const char* what() const throw() {
        	return "Excpetion Index is out of bounds.";
    	}
	};
};

#endif
