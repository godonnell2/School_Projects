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