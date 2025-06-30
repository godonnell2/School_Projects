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
/*
Copy Constructor: Creates a new Fixed object by copying 
the contents of an existing Fixed object (other).
could also do it this way 
 copy assignment operator does the copying
Fixed::Fixed(const Fixed &other) : _rawBits(other._rawBits) {}
*/
Fixed::~Fixed() {}

Fixed &Fixed::operator=(const Fixed &other) {
    if (this != &other) {
        _rawBits = other._rawBits;
    }
    return *this;
}
/*
Feature	Copy Constructor (Fixed(const Fixed& other))	        Copy Assignment Operator (Fixed& operator=(const Fixed& other))
Purpose	Initializes a new object from an existing one.	        Assigns one existing object's value to another existing object.
Syntax Usage	Fixed b(a); &lt;br> Fixed b = a; (direct initialization)	c = b; (after c has already been constructed)
*this State	*this is a newly created, uninitialized object.	    *this is an already existing, initialized object.
Mem Responsible for allocating new resources for the new object.	Responsible for managing resources (e.g., deallocating old, allocating new) of the existing object.
Self-Assignment	Not possible (you can't construct an object from itself).	Possible and must be handled (if (this != &other)).
Copy Assignment Operator: Assigns the value of one existing Fixed object (other) 
to another existing Fixed object (*this).
*/

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
/*
It's a non-member function, taking std::ostream& by reference (for the stream)
 and const Fixed& by reference (for the object to print).
It's an overloaded operator<< function. It lets you print your Fixed objects using std::cout (or any other std::ostream) 
 as if they were built-in types like int or float.
 . std::ostream &operator<<(...)
This defines a custom overload of the << operator for your Fixed class.
When someone tries to << a Fixed object, convert it to a float and stream that.”

out << fixed.toFloat();: It converts the Fixed object to a float using toFloat() 
and then inserts that float into the output stream. This means when you std::cout << someFixedObject;, 
it will print its decimal floating-point representation.
return out;: Returns the stream itself, allowing for chaining (e.g., std::cout << f1 << f2;).
*/

// Comparison operators
/*
hese operators overload the standard comparison symbols (>, <, >=, <=, ==, !=) for Fixed objects. They all work by comparing the underlying _rawBits integer values, which is efficient because _rawBits
 already holds the scaled, comparable values.
*/
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
//Arithmetic Operators
//These operators overload standard arithmetic symbols (+, -, *, /) 
//for Fixed objects.
Fixed Fixed::operator+(const Fixed &other) const {
    return Fixed(this->toFloat() + other.toFloat());
}
/*
Addition: Converts both Fixed operands to float, performs the float addition, 
and then constructs a new Fixed object from the float result using the Fixed(const float f) constructor.
Fixed(this->toFloat() + other.toFloat()): This is an implicit call to the Fixed(const float f) constructor.
*/
Fixed Fixed::operator-(const Fixed &other) const {
    return Fixed(this->toFloat() - other.toFloat());
}

Fixed Fixed::operator*(const Fixed &other) const {
    return Fixed(this->toFloat() * other.toFloat());
}

Fixed Fixed::operator/(const Fixed &other) const {
 
    return Fixed(this->toFloat() / other.toFloat());
}

Fixed &Fixed::operator++() {
    ++_rawBits;
    return *this;
}

// Postfix increment (a++)
Fixed Fixed::operator++(int) {
    Fixed temp = *this;
    ++_rawBits;
    return temp;
}

// Prefix decrement (--a)
Fixed &Fixed::operator--() {
    --_rawBits;
    return *this;
}

// Postfix decrement (a--)
Fixed Fixed::operator--(int) {
    Fixed temp = *this;
    --_rawBits;
    return temp;
}

Fixed &Fixed::min(Fixed &a, Fixed &b) {
    return (a < b) ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
    return (a < b) ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
    return (a > b) ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
    return (a > b) ? a : b;
}

