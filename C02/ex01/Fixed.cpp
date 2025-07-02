#include "Fixed.hpp"
#include <cmath>


Fixed::Fixed() : _rawBits(0) {
    std::cout << "Default constructor called" << std::endl;
}

// Int constructor
Fixed::Fixed(const int n) {
    std::cout << "Int constructor called" << std::endl;
    _rawBits = n << _fractionalBits; // Multiply by 256
}
//  n << x is = n multiply by 2 to the power of x (which we already defined as 8)
// left shift bitwise operator 2 to the power of 8 same as multiply by 256
// 32 bits of int into 24 bits for int and 8 bits for fractional part
// so lets say int n is 10 = 2560

// Float constructor
Fixed::Fixed(const float f) {
    std::cout << "Float constructor called" << std::endl;
    _rawBits = roundf(f * (1 << _fractionalBits)); // round(f * 256)
}
// f = 5.05f.
//rawBits = roundf(5.05f * (1 << 8))
//5.05f * 256 equals 1292.8f.

// Copy constructor
Fixed::Fixed(const Fixed &other) {
    std::cout << "Copy constructor called" << std::endl;
    this->_rawBits = other._rawBits;
}

//You are manipulating the objects themselves. & A reference is an alias, 
 //It's an assignment between two Fixed objects. 

// Assignment operator
Fixed &Fixed::operator=(const Fixed &other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        _rawBits = other._rawBits;
    return *this;
}
/*
checks if the object is being assigned to itself (e.g., c = c;).
For simple classes like Fixed (which only contain primitive types and no dynamic memory), this check isn't strictly necessary for correctness,
 as assigning an int to itself (_rawBits = _rawBits;) is harmless.
 owever, for more complex classes that manage dynamic memory (e.g., std::string or a custom array class), self-assignment without this check
  can lead to memory leaks or crashes. 
  Imagine if you freed the current object's memory before copying from other, 
  and other was the same object. You'd be trying to read from freed memory!
  Accesses the _rawBits member of the current object (*this).
  Calls the getRawBits() getter method on the other object to retrieve its raw bit value.
  Returns a reference to the current object.
  he copy assignment operator Fixed &Fixed::operator=(const Fixed &other) is responsible for correctly transferring the state 
  from one existing Fixed object to another existing Fixed object
  his operator, along with the copy constructor and destructor, forms the "Rule of Three/Five/Zero" in C++, 
  ensuring proper resource management and object behavior when copying.
*/

// Destructor
Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

// Conversion
float Fixed::toFloat() const {
    return (float)_rawBits / (1 << _fractionalBits); // Divide by 256
}
/*
 If _rawBits = 512:
(float)512 / 256 = 2.0f
_rawBits = 1.5 * 256 = 384
(float)384 / 256 = 1.5f
That means your internal integer value of 512 actually represents the float 2.0.
*/

int Fixed::toInt() const {
    return _rawBits >> _fractionalBits; // Divide by 256 (int)
}
/*

*/

// Getters/Setters
int Fixed::getRawBits() const {
    return _rawBits;
}

void Fixed::setRawBits(int const raw) {
    _rawBits = raw;
}

// Stream overload
std::ostream &operator<<(std::ostream &out, const Fixed &fixed) {
    out << fixed.toFloat();
    return out;
}
/*
 defining how to output a Fixed object with <<, 
 just like how you'd output an int, float, or string.
out << fixed.toFloat();
You're calling toFloat() to convert the internal fixed-point representation
 into a float.hat float gets streamed to out — typically std::cout.
return out; allows chaining:
Fixed a;
a.setRawBits(384);  // Represents 1.5
std::cout << a << std::endl;
Will output: 1.5
If you didn’t overloaded operator<<, you'd have to write:
std::cout << a.toFloat();
But now you can just do: std::cout << a;
An overloaded operator in C++ is a way to customize the behavior of built-in operators (like +, -, ==, <<, etc.)
 when they’re used with objects of your own class.
*/