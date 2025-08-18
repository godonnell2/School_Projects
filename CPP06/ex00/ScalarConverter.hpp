#ifndef SCALAR_CONVERTER_H
# define SCALAR_CONVERTER_H

# include <iostream>
# include <string>
# include <limits>
# include <iomanip>
# include <cctype>
# include <cmath>

class ScalarConverter {
    
    private:
        ScalarConverter();
        ~ScalarConverter();
        ScalarConverter(const ScalarConverter &copy);
        ScalarConverter &operator=(const ScalarConverter &other);

    public:
        static void convert(const std::string &input);
};

#endif