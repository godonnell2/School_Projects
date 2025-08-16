#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    const int size = 4;
    AAnimal* animals[size];
    //AAnimal a;
    for (int i = 0; i < size; ++i) {
        if (i < size / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    std::cout << "\n--- Making sounds ---\n";
    for (int i = 0; i < size; ++i)
        animals[i]->makeSound();

    std::cout << "\n--- Deleting animals ---\n";
    for (int i = 0; i < size; ++i)
        delete animals[i];

    return 0;
}

/*
AAnimal is now an abstract class,

ou cannot do AAnimal a; anymore, the compiler will refuse.
 i.e. it contains at least one pure virtual function, like:
Polymorphism	Calls to makeSound() resolved at runtime through base pointers
Array of Base Class Pointers	AAnimal* animals[4] lets you treat Dog and Cat uniformly
 Dynamic Memory	Still using Brain class, still doing deep copies, still deleting correctly
 Enforced Interface	Dog and Cat must implement makeSound() or they'll fail to compile

when create virtual fn the compiler creates a vtable (virtual table) for the class.
This table contains pointers to the actual function implementations for each type.
For AAnimal, the vtable contains a pointer for makeSound(), but since it’s pure virtual, it points to a “pure virtual function called” handler.

For derived classes like Dog or Cat, their vtables have makeSound() pointing to their own implementations.
animal is more a concept or category doesnt make sense to have instance of somethign that abstract
*/