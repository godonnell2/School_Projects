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
/* 
in this particular exercise
created two derived objects: a Dog and a Cat.
so first the animal constructor is called cos it's the base
then dog or cat ie derived is called
polymorphism ie cat meow dog barks (virtual)
derived destructor is called first then animal only works cos animal has a virtual destructor
Part 4: Copy and Assignment Test
created a dog and made a copy both animal and dog constructor called
then do it with cat 
hows correct inheritance of copy constructors and assignment operators.
All the dynamically or locally created objects are being destructed.
*/
/*
Concept	What You're Doing
Polymorphism	Calling overridden methods via base class pointers
Virtual functions	Marking functions with virtual in base class
Inheritance	Creating derived classes that override behavior
Virtual destructors	Ensuring safe memory management in polymorphic use
Class hierarchy	Designing clean OOP hierarchies with base and derived classes
efine a base class with a virtual function.

Then, derived classes override that function.

When you call the function through a pointer/reference to the base class, the correct override gets called, depending on the actual object type.

2. Proper Use of Inheritance
You create a base class (e.g., Animal)

Then derive child classes (e.g., Cat, Dog) from it.

3. Why Virtual Destructors Matter
If you delete an object through a base class pointer and the base class does not 
have a virtual destructor, it causes undefined behavior (memory leaks, etc.).
*/

/*
VIRTUAL!!!
In C++, the virtual keyword is used to enable polymorphism — 
that is, to allow method overriding in derived classes to work correctly when accessed through a base class pointer or reference.

🚩 Without virtual
If you don’t use virtual, then method calls on base class pointers will not 
call the derived class version — they will always call the base class version,
 even if the actual object is of a derived type.
 Method Dispatch	Enables runtime method resolution
Method Overriding	Lets derived class override base method
Destructors	Ensures full cleanup via base pointer
Polymorphism	Allows correct method call through Base* or Base&
*/