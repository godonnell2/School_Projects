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