#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    std::cout << "=== Creating Animals ===\n";
    const Animal* a1 = new Dog();
    const Animal* a2 = new Cat();

    std::cout << "\n=== Making Sounds ===\n";
    a1->makeSound(); // should call Dog::makeSound
    a2->makeSound(); // should call Cat::makeSound

    std::cout << "\n=== Deleting Animals ===\n";
    delete a1;
    delete a2;

    std::cout << "\n=== Copy and Assignment Test ===\n";
    Dog dog1;
    Dog dog2 = dog1;
    Dog dog3;
    dog3 = dog1;

    Cat cat1;
    Cat cat2 = cat1;
    Cat cat3;
    cat3 = cat1;

    return 0;
}