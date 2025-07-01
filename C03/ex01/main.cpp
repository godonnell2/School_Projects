#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
    ClapTrap clap("CL4P-TP");
    ScavTrap scav("Serena");

    clap.attack("a rock");
    scav.attack("an intruder");

    clap.takeDamage(5);
    scav.takeDamage(15);

    clap.beRepaired(3);
    scav.beRepaired(10);

    return 0;
}
/*
 CL4P-TP is a direct ClapTrap object, it uses its own attackDamage value, 
 which was set to 0 during its construction. cant alter attack cos it only takes a string as arg
 showign that scav is overriding ClapTraps
*/