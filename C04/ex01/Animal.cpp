#include "Animal.hpp"

Animal::Animal() {
    std::cout << "Animal constructor called\n";
}

Animal::~Animal() {
    std::cout << "Animal destructor called\n";
}

std::string Animal::getType() const {
    return type;
}