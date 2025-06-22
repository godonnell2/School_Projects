#include "Fixed.hpp"

// Constructors
Fixed::Fixed() : _rawBits(0) {}

Fixed::Fixed(const int n) {
    _rawBits = n << _fractionalBits;
}

Fixed::Fixed(const float f) {
    _rawBits = roundf(f * (1 << _fractionalBits));
}

Fixed::Fixed(const Fixed &other) {
    *this = other;
}

Fixed::~Fixed() {}

Fixed &Fixed::operator=(const Fixed &other) {
    if (this != &other) {
        _rawBits = other._rawBits;
    }
    return *this;
}

// Getters and setters
int Fixed::getRawBits() const {
    return _rawBits;
}

void Fixed::setRawBits(int const raw) {
    _rawBits = raw;
}

// Conversion functions
float Fixed::toFloat() const {
    return (float)_rawBits / (1 << _fractionalBits);
}

int Fixed::toInt() const {
    return _rawBits >> _fractionalBits;
}

// Stream output
std::ostream &operator<<(std::ostream &out, const Fixed &fixed) {
    out << fixed.toFloat();
    return out;
}

// Comparison operators
bool Fixed::operator>(const Fixed &other) const {
    return _rawBits > other._rawBits;
}

bool Fixed::operator<(const Fixed &other) const {
    return _rawBits < other._rawBits;
}

bool Fixed::operator>=(const Fixed &other) const {
    return _rawBits >= other._rawBits;
}

bool Fixed::operator<=(const Fixed &other) const {
    return _rawBits <= other._rawBits;
}

bool Fixed::operator==(const Fixed &other) const {
    return _rawBits == other._rawBits;
}

bool Fixed::operator!=(const Fixed &other) const {
    return _rawBits != other._rawBits;
}

// Arithmetic operators
Fixed Fixed::operator+(const Fixed &other) const {
    return Fixed(this->toFloat() + other.toFloat());
}

Fixed Fixed::operator-(const Fixed &other) const {
    return Fixed(this->toFloat() - other.toFloat());
}

Fixed Fixed::operator*(const Fixed &other) const {
    return Fixed(this->toFloat() * other.toFloat());
}

Fixed Fixed::operator/(const Fixed &other) const {
    if (other._rawBits == 0) {
        std::cerr << "Error: Division by zero." << std::endl;
        return Fixed(0);
    }
    return Fixed(this->toFloat() / other.toFloat());
}