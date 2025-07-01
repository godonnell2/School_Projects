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
we added a brain class obvie
every dog or cat his its own brain 
allocatin and deallocing brain dynamically 
Concept	Description
🧠 Dynamic Memory	Brain object is dynamically allocated in Dog and Cat
🧹 Rule of Three	You implement copy constructor, assignment operator, and destructor
✅ Deep Copy	Prevents shared pointers to the same Brain (no shallow copies)
🔁 Object Copying	You're testing object cloning and assignment
🔒 Encapsulation	Brain is probably private and only manipulated via Dog/Cat


*/