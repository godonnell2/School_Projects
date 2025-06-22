#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
private:
    int _rawBits;
    static const int _fractionalBits = 8;

public:
    Fixed();                         // Default constructor
    Fixed(const int n);              // New: int constructor
    Fixed(const float f);            // New: float constructor
    Fixed(const Fixed &other);       // Copy constructor
    Fixed &operator=(const Fixed &other); // Assignment
    ~Fixed();                        // Destructor

    int getRawBits() const;
    void setRawBits(int const raw);

    float toFloat() const;           // New: convert to float
    int toInt() const;               // New: convert to int
};

// Stream insertion overload
std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif