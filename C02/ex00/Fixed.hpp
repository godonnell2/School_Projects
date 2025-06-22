#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
private:
    int _rawBits;
    static const int _fractionalBits = 8;

public:
    Fixed();                              // Default constructor
    Fixed(const Fixed &other);            // Copy constructor
    Fixed &operator=(const Fixed &other); // Copy assignment
    ~Fixed();                             // Destructor

    int getRawBits() const;
    void setRawBits(int const raw);
};

#endif

/*

🧠 What is Canonical Orthodox Form?
It refers to the "big four" functions you should implement in a class when you need to manage resource copies or behavior carefully:

Default constructor

Copy constructor

Copy assignment operator

Destructor


*/