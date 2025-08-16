#include "Cat.hpp"

Cat::Cat() {
    type = "Cat";
    std::cout << "Cat: Constructor called\n";
}

Cat::Cat(const Cat& other) : Animal(other) {
    std::cout << "Cat: Copy constructor called\n";
}

Cat& Cat::operator=(const Cat& other) {
    std::cout << "Cat: Assignment operator called\n";
    if (this != &other) {
        Animal::operator=(other); // copy Animal part
    }
    return *this;
}

Cat::~Cat() {
    std::cout << "Cat: Destructor called\n";
}

void Cat::makeSound() const {
    std::cout << "Meow meow!\n";
}
