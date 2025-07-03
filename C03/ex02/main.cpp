#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

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
 

    std::cout << "\n=== Destruction ===" << std::endl;
    return 0;
}
/*
Even though ScavTrap and FragTrap both inherit from ClapTrap, 
ClapTrap is only constructed once — this happens because it is marked as a virtual base class
 or because of constructor resolution using ClapTrap(name + "_clap_name").
*/
/*
both inherit from claptrap and then builds on it
These show polymorphic behavior:
ScavTrap Serena aggressively attacks intruder, dealing 20 points of damage!
FragTrap FR4G launches a huge attack on mutant, dealing 30 damage!
Polymorphism lets you call the same function on different types of objects and get different behavior.
high five shows fragtrap has its own unique method
Derived class destructors run first (FragTrap, ScavTrap)
Then base class destructor (ClapTrap)

F

*/