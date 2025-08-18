#include "ScalarConverter.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./convert <value>" << std::endl;
        return 1;
    }

    std::string input = argv[1];
    ScalarConverter::convert(input);
    return 0;
}

/*
Type Conversion (Casting)

How to take a string and interpret it as char, int, float, double.

How to use static_cast, dynamic_cast, reinterpret_cast, const_cast (though here mostly static_cast).

Input Parsing

You receive input as a string (e.g., "nan", "42.0f", "a") and must figure out what it represents.

Special Floating-Point Values

Handle nan, +inf, -inf, nanf, +inff, -inff.

Impossibility Cases

Some conversions don’t make sense and must print "impossible".
Example: "nan" cannot be converted to char or int.

Display Rules

If a char is not printable, say "Non displayable".

Floats always print with a .0f if they’re whole numbers.

Doubles print with .0 if whole.
grace@MacBook-Air-2 ex00 % ./ScalarConverter a
grace@MacBook-Air-2 ex00 % ./ScalarConverter 2147483647 
grace@MacBook-Air-2 ex00 % ./ScalarConverter -2147483648 
grace@MacBook-Air-2 ex00 % ./ScalarConverter 42.0f
./ScalarConverter -inff
./ScalarConverter nanf

*/