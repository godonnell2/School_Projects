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

//constructor call is type 
//Animal a("Dog"); "Dog" initializes the private _type member.
//A getter is just a function that lets you get the value of 
//a private (or protected) member variable in a class.
// Virtual methods are for behavior that changes across derived classes.