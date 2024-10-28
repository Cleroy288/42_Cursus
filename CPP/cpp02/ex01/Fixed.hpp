#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed {
private:
    int fixedPointValue;
    static const int fractionalBits = 8;

public:
    Fixed();  
    Fixed(const int intValue);
    Fixed(const float floatValue);
    Fixed(const Fixed &src);
    ~Fixed();

    Fixed &operator=(const Fixed &rhs);

    int getRawBits(void) const;
    void setRawBits(int const raw);

    float toFloat(void) const;
    int toInt(void) const;
};

    std::ostream &operator<<(std::ostream &os, const Fixed &fixed);


#endif
