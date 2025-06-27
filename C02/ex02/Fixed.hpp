#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed {
private:
    int _rawBits;
    static const int _fractionalBits = 8;

public:
    Fixed();
    Fixed(const int n);
    Fixed(const float f);
    Fixed(const Fixed &other);
    ~Fixed();

    Fixed &operator=(const Fixed &other);

    float toFloat() const;
    int toInt() const;
    int getRawBits() const;
    void setRawBits(int const raw);

    // Comparison operators
    bool operator>(const Fixed &other) const;
    bool operator<(const Fixed &other) const;
    bool operator>=(const Fixed &other) const;
    bool operator<=(const Fixed &other) const;
    bool operator==(const Fixed &other) const;
    bool operator!=(const Fixed &other) const;

    // Arithmetic operators
    Fixed operator+(const Fixed &other) const;
    Fixed operator-(const Fixed &other) const;
    Fixed operator*(const Fixed &other) const;
    Fixed operator/(const Fixed &other) const;


    //Decrement/increment operators

    Fixed& operator++();
    Fixed& operator--();

    Fixed operator++(int);
    Fixed operator--(int);

    //min max operators

static Fixed &min(Fixed &a, Fixed &b);
 static const Fixed &min(const Fixed &a, const Fixed &b);
static Fixed &max(Fixed &a, Fixed &b);

static const Fixed &max(const Fixed &a, const Fixed &b);


};

// Overload stream operator
std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif