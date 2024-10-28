#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template <typename T, typename Funct>
void iter(T* array, size_t length, Funct func) {
    for (size_t i = 0; i < length; ++i) {
        func(array[i]);
    }
}

template <typename T>
void printElement(const T& element) {
    std::cout << element << std::endl;
}

#endif



