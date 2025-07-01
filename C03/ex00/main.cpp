#include "ClapTrap.hpp"

int main() {
    ClapTrap a("CL4P-TP");
    ClapTrap b("Scavvy");

    a.attack("Scavvy");
    b.takeDamage(3);

    b.attack("CL4P-TP");
    a.takeDamage(5);

    a.beRepaired(4);
    b.beRepaired(2);

    return 0;
}
/*
bot2 (Scavvy) is destroyed first (LIFO order),
*/
/*

Inheritance	How a subclass can reuse and extend the functionality of a parent class
Constructor/Destructor chaining	How base and derived constructors/destructors 
are called in order
Access control (protected)	Using protected to allow subclass access to base attributes
Polymorphism (early stage)	Not full virtual functions yet, but understanding how derived classes override behavior
Method overriding	Specializing functions in the subclass
Code reuse	Using inheritance to avoid copy-pasting base logic
Well, when talking about inheritance usually the saying is "composition over inheritance"
When doing systems design
So instead of your X being a specialization of Y, your X "contains" a Y and uses it internally
*/