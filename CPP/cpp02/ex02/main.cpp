#include "Fixed.hpp"
#include <iostream>


/*
Pour quoi un F à la fin du nombre ? Car sinon le nombre sera intéprété comme un double 

==> We must add the suffix f or F at the end of a float value. This is because the compiler interprets decimal values without the suffix as double .
*/


int main(void) {
    Fixed a;
    Fixed const b(Fixed(5.05f) * Fixed(2));
    std::cout << a << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << Fixed::max(a, b) << std::endl;

    std::cout<<"------- ==== other test ==== --------"<<std::endl;

    std::cout<<"----- ==== opérator test ==== -----"<<std::endl;
    if (a == b)
        std::cout << "opérator == is real" <<std::endl;
    if (a < b)
        std::cout << "operator < is real" <<std::endl;
    if (a > b)
        std::cout << "operator > is real"<<std::endl;
    if (a != b)
        std::cout<< "operator != is real"<<std::endl;
    if (a <= b)
        std::cout<<"opérator <= is real"<<std::endl;
    if (a >= b)
        std::cout<<"opérator >= is real"<<std::endl;

    std::cout<<"----- ==== min - max test ==== -----"<<std::endl;
    std::cout<<"min "<<Fixed::min(a, b)<<std::endl;
    std::cout<<"max "<<Fixed::max(a, b)<<std::endl;

    std::cout << "----- ==== ++ -- test ==== -----" << std::endl;

    Fixed postIncrement = a++;
    Fixed postDecrement = a--;
    std::cout << "just a " << a << std::endl;
    std::cout << "a++ " << postIncrement << std::endl;
    std::cout << "a-- " << postDecrement << std::endl;
    std::cout << "++a " << ++a << std::endl;
    std::cout << "--a " << --a << std::endl;

    std::cout << "----- ==== + - * / test ==== -----" << std::endl;

    std::cout << "+ " << a + b << std::endl;
    std::cout << "* " << a * b << std::endl;
    std::cout << "- " << a - b << std::endl;
    std::cout << "/ " << a / b << std::endl;

    std::cout << "----- ==== Assignment operator test ==== -----" << std::endl;
    Fixed c;
    std::cout << "Before assignment, c = " << c << std::endl;
    c = b;
    std::cout << "After assignment, c = " << c << std::endl;


    std::cout << "----- ==== constructeur de copie ==== -----" << std::endl;
    Fixed l(b);
    std::cout<<"l "<<l<<std::endl;

    std::cout << "----- ==== constructeur de int ==== -----" << std::endl;
    Fixed o(10);
    std::cout<<"o "<<o<<std::endl;

    std::cout << "----- ==== constructeur de float ==== -----" << std::endl;

    Fixed k(10.05f);
    std::cout<<"k "<<k<<std::endl;


    return 0;
}
