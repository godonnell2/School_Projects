#include "DiamondTrap.hpp"

int main() {
    DiamondTrap d("Shiny");
    d.attack("target dummy");
    d.whoAmI();
    d.takeDamage(30);
    d.beRepaired(20);
    return 0;
}