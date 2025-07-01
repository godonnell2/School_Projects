#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
    ClapTrap clap("CL4P");
    ScavTrap scav("Serena");
    FragTrap frag("FR4G");

    clap.attack("target dummy");
    scav.attack("intruder");
    frag.attack("mutant");

    clap.beRepaired(3);
    scav.beRepaired(5);
    frag.beRepaired(10);

    clap.takeDamage(2);
    scav.takeDamage(20);
    frag.takeDamage(40);

    frag.highFivesGuys();

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