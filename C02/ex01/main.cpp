#include "Fixed.hpp"

int main(void) {
    Fixed a;
    Fixed const b(10);
    Fixed const c(42.42f);
    Fixed const d(b); //copy constructor 

    a = Fixed(1234.4321f); //float constructor for a temp obj then assignemnt 

    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;

    std::cout << "a is " << a.toInt() << " as integer" << std::endl;
    std::cout << "b is " << b.toInt() << " as integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as integer" << std::endl;

    return 0;
}

/*
C++ chooses the constructor based on the type of the argument.
You’re seeing one Destructor called line at the end because:
The temporary Fixed(1234.4321f) gets destroyed
42.42f * 256 = 10859.52
roundf(10859.52) = 10860
Then in toFloat(): 10860 / 256 = 42.421875 c is 42.4219 rounded to 4 decimal places by cot
*/