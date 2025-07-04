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
eature	Evidence in Output
Multiple inheritance	DiamondTrap uses both ScavTrap and FragTrap
Name conflicts	Resolved with _name and _clap_name 3 classes have a member called _name
scavtrap and fragtrap inherit name from claptrap but diamond class has its own name
ClapTrap(name + "_clap_name") // Calls ClapTrap constructor with a modified name
this->_name = name;           // DiamondTrap’s own name
You’re sidestepping ambiguity by:

Giving DiamondTrap its own _name

Passing a modified string to ClapTrap's constructor

Accessing ClapTrap::_name explicitly when needed
Function reuse	attack(), repair(), and takeDamage() called
ClapTrap::_name → e.g. "Shiny_clap_name" (used internally)
Polymorphism / overrides	You call different behavior depending on inheritance
Constructor chaining	Base → Intermediate → Final class
Destructor order	Final class → Base class (reverse of construction)
*/