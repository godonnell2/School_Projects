#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    const int size = 4;
    Animal* animals[size];

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
we added a brain class obvie but it doesnt have a base class
every dog or cat his its own brain 
allocatin and deallocing brain dynamically 
Base -> member obj constructors (brain) -> derived class constructor

Cat and Dog each have a Brain pointer.
Deep copy means that when you copy a Cat or Dog, 
you allocate a new Brain and copy the ideas over,
 rather than just copying the pointer.
 Then deleting one animal would delete the Brain object 
 and leave the other animal with a dangling pointer.
 By observing that each Brain is constructed and destructed independently,
  we can see that each animal owns its own Brain → deep copy is working.
  This happens because your destructor deletes the Brain explicitly before printing "Dog destructor called".

 Dynamic Memory	Brain object is dynamically allocated in Dog and Cat
 Deep Copy	Prevents shared pointers to the same Brain (no shallow copies)
bject Copying	You're testing object cloning and assignment
 Encapsulation	Brain is private and only manipulated via Dog/Cat


*/