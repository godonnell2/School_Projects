#include "Cat.hpp"

Cat::Cat() : brain(new Brain()) {
    type = "Cat";
    std::cout << "Cat constructor called\n";
}

Cat::Cat(const Cat& other) : Animal(other), brain(new Brain(*other.brain)) {
    std::cout << "Cat copy constructor called\n";
    type = other.type;
}

Cat& Cat::operator=(const Cat& other) {
    std::cout << "Cat assignment operator called\n";
    if (this != &other) {
         Animal::operator=(other);  // copy the base class part
        *brain = *other.brain;
    }
    return *this;
}

Cat::~Cat() {
    delete brain;
    std::cout << "Cat destructor called\n";
}

void Cat::makeSound() const {
    std::cout << "Meow meow!\n";
}