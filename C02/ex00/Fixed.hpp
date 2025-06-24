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
It refers to the "big four" functions you should implement 
in a class when you need to manage resource copies or behavior carefully:

Default constructor
Copy constructor
Copy assignment operator
Destructor

static: This means _fractionalBits is a class-level member, 
not an instance-level member. 
There is only one copy of _fractionalBits shared by all Fixed objects.
 You don't need a Fixed object to access it (e.g., you could use Fixed::_fractionalBits).
 defines the precision of your fixed-point numbers (8 bits for the fractional part).
*/

/*
 // Line 1: Object 'a' is created
    Fixed a; // Calls the Default Constructor

    // Line 2: Object 'b' is created as a copy of 'a'
    Fixed b(a); // Calls the Copy Constructor
Copy Constructor (Fixed b(a);): Creates a new Fixed object by copying the state from an existing Fixed object.
    
    // 'b._rawBits' gets the value of 'a._rawBits' (which is 0)

    // Line 3: Object 'c' is created


    // Line 4: Object 'c' is assigned the value of 'b'
    c = b; // Calls the Copy Assignment Operator

    // Output: "Copy assignment operator called"
    // 'c._rawBits' gets the value of 'b._rawBits' (which is 0)

    // End of main function: Objects go out of scope in reverse order of creation
    // First 'c' is destroyed, then 'b', then 'a'.

    // Output: "Destructor called" (for c)
    // Output: "Destructor called" (for b)
    // Output: "Destructor called" (for a)
     called LIFO (Last-In, First-Out) STACK BASED MEM MGMT
*/
