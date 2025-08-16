#include "Dog.hpp"

Dog::Dog() {
    type = "Dog";
    std::cout << "Dog: Constructor called\n";
}

Dog::Dog(const Dog& other) : Animal(other) {
    std::cout << "Dog: Copy constructor called\n";
}

Dog& Dog::operator=(const Dog& other) {
    std::cout << "Dog: Assignment operator called\n";
    if (this != &other) {
        Animal::operator=(other); // copy Animal part
    }
    return *this;
}

Dog::~Dog() {
    std::cout << "Dog: Destructor called\n";
}

void Dog::makeSound() const {
    std::cout << "Woof woof!\n";
}