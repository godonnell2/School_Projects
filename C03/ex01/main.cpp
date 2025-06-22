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