#include "DiamondTrap.hpp"

int main() {
    std::cout << "\n=== FragTrap Construction ===" << std::endl;
    FragTrap frag1("FRAG-1");

    std::cout << "\n=== FragTrap Actions ===" << std::endl;
    frag1.attack("Target");
    frag1.highFivesGuys();
    frag1.takeDamage(40);
    frag1.beRepaired(25);

    std::cout << "\n=== FragTrap Copying ===" << std::endl;
    FragTrap frag2(frag1);
    FragTrap frag3("frag3");
    frag3 = frag2;

    std::cout << "\n=== ScavTrap Construction ===" << std::endl;
    ScavTrap scav1("SCAV-1");
    scav1.attack("Another Target");
    scav1.guardGate();

    std::cout << "\n=== Destruction ===" << std::endl;
    return 0;
}

/*
Diamond Prob CPP
            ClapTrap
           /      \
     ScavTrap     FragTrap
           \      /
         DiamondTrap
eature	Evidence in Output
ScavTrap and FragTrap both inherit from ClapTrap

DiamondTrap inherits from both

So… DiamondTrap now has two copies of ClapTrap, unless you're careful.
Use virtual inheritance in real-world C++, but you’re not allowed to in this project.

Multiple inheritance	DiamondTrap uses both ScavTrap and FragTrap
Name conflicts	Resolved with _name and _clap_name 3 classes have a member called _name
scavtrap and fragtrap inherit name from claptrap but diamond class has its own name
ClapTrap(name + "_clap_name") // Calls ClapTrap constructor with a modified name
this->_name = name;           // DiamondTrap’s own name
You’re sidestepping ambiguity by:

Giving DiamondTrap its own _name

Passing a modified string to ClapTrap's constructor

Accessing ClapTrap::_name explicitly when needed
ou now have two inherited attack() functions:

ScavTrap::attack()

FragTrap::attack()

In your DiamondTrap, you should explicitly choose one:
This shows you understand method resolution in multiple inheritance.
This method prints both:

DiamondTrap's own _name

ClapTrap::_name (which is hidden unless you access it directly)

You know how to reference hidden inherited members explicitly

You understand what name collision means

Function reuse	attack(), repair(), and takeDamage() called
ClapTrap::_name → e.g. "Shiny_clap_name" (used internally)
Polymorphism / overrides	You call different behavior depending on inheritance
Constructor chaining	Base → Intermediate → Final class
Destructor order	Final class → Base class (reverse of construction)
*/