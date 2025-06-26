#include "Animal.hpp"

Animal::Animal() : type("Animal") {
    std::cout << "Animal: Default constructor called\n";
}

Animal::Animal(const Animal& other) : type(other.type) {
    std::cout << "Animal: Copy constructor called\n";
}

Animal& Animal::operator=(const Animal& other) {
    std::cout << "Animal: Assignment operator called\n";
    if (this != &other)
        type = other.type;
    return *this;
}

Animal::~Animal() {
    std::cout << "Animal: Destructor called\n";
}

void Animal::makeSound() const {
    std::cout << "* generic animal noise *\n";
}

std::string Animal::getType() const {
    return type;
}