#include "ClapTrap.hpp"

int main() {
 

    ClapTrap clap1("CLAP-1");
    ClapTrap grace("Grace");

    clap1.attack("Grace");
    grace.takeDamage(5);
    grace.beRepaired(3);

    grace.takeDamage(10);
    grace.beRepaired(5);
    return 0;
}
/*
Encapsulating behavior (attack(), takeDamage(), beRepaired())
bot2 (Scavvy) is destroyed first (LIFO order),
Implemented actions: attack, takeDamage, beRepaired using classes
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