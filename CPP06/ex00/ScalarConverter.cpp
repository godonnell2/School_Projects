#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {
}

ScalarConverter::~ScalarConverter() {
}

ScalarConverter::ScalarConverter(const ScalarConverter &copy) {
    *this = copy;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other) {
    (void)other;
    return *this;
}

bool    isInt(const std::string &input) {
    char *end;
    long num = std::strtol(input.c_str(), &end, 10);
    return (*end == '\0' && num >= std::numeric_limits<int>::min()
        && num <= std::numeric_limits<int>::max());
}

bool isFloat(const std::string &input) {
    if (input.find('.') == std::string::npos)
        return false;
    char lastChar = input.back();
    if (lastChar != 'f')
        return false;
    std::string floatString = input.substr(0, input.length() -1);
    char *end;
    std::strtod(floatString.c_str(), &end);
    return (*end == '\0');
}

bool isDouble(const std::string &input) {
    char *end;
    std::strtod(input.c_str(), &end);
    return (input.find('.') != std::string::npos && *end == '\0');
}

bool isChar(const std::string &input) {
    return (input.length() == 1 && !std::isdigit(input[0]));
}

bool isSpecial(const std::string &input) {
    return (input == "+inff" || input == "-inff"
        || input == "+inf" || input == "-inf"
        || input == "nan" || input == "nanf");
}

void convertInt(long num) {
    std::cout << "char: ";
    if (num >= 0 && num <= 127) {
        if (num == 0)
            std::cout << "Non displayable" << std::endl;
        else if (std::isprint(num))
            std::cout << "'" << static_cast<char>(num) << "'" << std::endl;
        else
            std::cout << "Non displayable" << std::endl;
    }
    else
        std::cout << "impossible" << std::endl;

    std::cout << "int: " << num << std::endl;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: " << static_cast<float>(num) << "f" << std::endl;
    std::cout << "double: " << static_cast<double>(num) << std::endl;
}

void convertDouble(double num) {
    std::cout << "char: ";
    if (num >= 0 && num <= 127) {
        if (num == 0)
            std::cout << "Non displayable" << std::endl;
        else if (std::isprint(num))
            std::cout << "'" << static_cast<char>(num) << "'" << std::endl;
        else
            std::cout << "Non displayable" << std::endl;
    }
    else
        std::cout << "impossible" << std::endl;

    std::cout << "int: " << static_cast<int>(num) << std::endl;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: " << static_cast<float>(num) << "f" << std::endl;
    std::cout << "double: " << num << std::endl;
}

void convertFloat(float num) {
    convertDouble(static_cast<double>(num));
}

void convertChar(char c) {
    std::cout << "char: " << c << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: " << static_cast<float>(c) << std::endl;
    std::cout << "double: " << static_cast<double>(c) << std::endl;
}

void convertSpecial(const std::string &input) {
    if (input == "+inff" || input == "-inff") {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: " << input << std::endl;
        std::cout << "double: " << (input == "+inff" ? "+inf" : "-inf") << std::endl;
    }
    else if (input == "+inf" || input == "-inf") {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: " << (input == "+inf" ? "+inff" : "-inff") << std::endl;
        std::cout << "double: " << input << std::endl;
    }
    else if (input == "nan" || input == "nanf") {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: " << "nanf" << std::endl;
        std::cout << "double: " << "nan" << std::endl;
    }
}

void ScalarConverter::convert(const std::string &input) {
    if (isSpecial(input))
        convertSpecial(input);
    else if (isFloat(input)) {
        float num = std::atof(input.c_str());
        convertFloat(num);
    }
    else if (isDouble(input)) {
        double num = std::atof(input.c_str());
        convertDouble(num);
    }
    else if (isChar(input))
        convertChar(input[0]);
    else if (isInt(input)) {
        long num = std::strtol(input.c_str(), nullptr, 10);
        convertInt(num);
    }
    else
        std::cout << "Invalid input" << std::endl;
}