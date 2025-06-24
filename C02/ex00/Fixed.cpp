#include "Fixed.hpp"

Fixed::Fixed() : _rawBits(0) {
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other) {
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

Fixed &Fixed::operator=(const Fixed &other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) {
        this->_rawBits = other.getRawBits();
    }
    return *this;
}

Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits() const {
    std::cout << "getRawBits member function called" << std::endl;
    return _rawBits;
}

void Fixed::setRawBits(int const raw) {
    _rawBits = raw;
}


/*
he Signature: Fixed &Fixed::operator=(const Fixed &other)
Fixed & (Return Type):

This specifies that the operator returns a reference to a Fixed object.
Specifically, it returns *this (a reference to the object on the left-hand side of the assignment).
Why return Fixed&? This is a convention that allows for chaining of assignments. For example:
C++

Fixed f1, f2, f3;
f1 = f2 = f3; // f2 = f3 returns f2 by reference, then f1 = f2 assigns its value
If you returned void or Fixed by value, chaining wouldn't work as expected or would be inefficient.
Fixed:: (Scope Resolution Operator):

Indicates that operator= is a member function of the Fixed class.
operator= (Operator Overload):

This is the special syntax in C++ for overloading an operator. When the compiler sees the = symbol used between two Fixed objects, it knows to call this specific member function.
(const Fixed &other) (Parameter):

const: This indicates that the other object (the one on the right-hand side of the assignment) will not be modified by this operation. This is good practice for copy operations.
Fixed &: The parameter is passed by constant reference.
Reference (&): This avoids making a full copy of the other object when passing it to the function. Instead, it gets a direct reference to the original other object, which is more efficient, especially for larger objects.
Fixed: The type of the object being assigned from.
The Body of the Function:
C++

{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) {
        this->_rawBits = other.getRawBits();
    }
    return *this;
}
std::cout << "Copy assignment operator called" << std::endl;

This is purely for demonstration and debugging. It prints a message to the console every time this operator is invoked, helping you trace the program's execution flow. In a production application, you would remove such print statements.
if (this != &other) (Self-Assignment Check):

this: Inside a non-static member function, this is a special pointer that points to the current object on which the member function is being called. So, this points to the object on the left-hand side of the = operator (e.g., if c = b;, then this points to c).
&other: This takes the memory address of the other object (the one on the right-hand side, e.g., b).
this != &other: This condition checks if the address of the current object is different from the address of the other object. In simpler terms, it checks if the object is being assigned to itself (e.g., c = c;).
Why is this check important?
For simple classes like Fixed (which only contain primitive types and no dynamic memory), this check isn't strictly necessary for correctness, as assigning an int to itself (_rawBits = _rawBits;) is harmless.
However, for more complex classes that manage dynamic memory (e.g., std::string or a custom array class), self-assignment without this check can lead to memory leaks or crashes. Imagine if you freed the current object's memory before copying from other, and other was the same object. You'd be trying to read from freed memory!
It's a crucial defensive programming technique and a standard part of correctly implementing the copy assignment operator.
this->_rawBits = other.getRawBits();

This line performs the actual copying of data.
this->_rawBits: Accesses the _rawBits member of the current object (*this).
other.getRawBits(): Calls the getRawBits() getter method on the other object to retrieve its raw bit value.
The value from other's _rawBits is then assigned to the current object's _rawBits. This is a member-wise copy.
return *this;

Returns a reference to the current object. As explained above, this enables assignment chaining (f1 = f2 = f3;). The * dereferences the this pointer to get the actual Fixed object itself, and then it's returned by reference.
In Summary:
The copy assignment operator Fixed &Fixed::operator=(const Fixed &other) is responsible for correctly transferring the state from one existing Fixed object to another existing Fixed object. It typically involves:

Self-assignment check to prevent issues when an object is assigned to itself.
Copying relevant data members from the other object to the current object.
Returning a reference to *this to allow for chained assignments.
This operator, along with the copy constructor and destructor, forms the "Rule of Three/Five/Zero" in C++, ensuring proper resource management and object behavior when copying.

*/