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
AAnimal is now an abstract class,
 i.e. it contains at least one pure virtual function, like:
 You're still applying the Rule of Three 
 Concept	Description
🧱 Abstract Classes	AAnimal is abstract: contains at least one pure virtual function
🔁 Polymorphism	Calls to makeSound() resolved at runtime through base pointers
📦 Array of Base Class Pointers	AAnimal* animals[4] lets you treat Dog and Cat uniformly
🧹 Virtual Destructors	Ensures proper cleanup of derived types
🧠 Dynamic Memory	Still using Brain class, still doing deep copies, still deleting correctly
🔒 Enforced Interface	Dog and Cat must implement makeSound() or they'll fail to compile


*/