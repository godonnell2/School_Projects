#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() {
    diamondName = "Default";
    name = diamondName + "_clap_name";
    hitPoints = FragTrap::hitPoints;
    energyPoints = ScavTrap::energyPoints;
    attackDamage = FragTrap::attackDamage;
    std::cout << "DiamondTrap " << diamondName << " constructed\n";
}

DiamondTrap::DiamondTrap(const std::string& _name) {
    diamondName = _name;
    name = _name + "_clap_name";
    hitPoints = FragTrap::hitPoints;
    energyPoints = ScavTrap::energyPoints;
    attackDamage = FragTrap::attackDamage;
    std::cout << "DiamondTrap " << diamondName << " constructed\n";
}

DiamondTrap::~DiamondTrap() {
    std::cout << "DiamondTrap " << diamondName << " destructed\n";
}

void DiamondTrap::whoAmI() {
    std::cout << "I am " << diamondName << ", and my ClapTrap name is " << name << "\n";
}

void DiamondTrap::attack(const std::string& target) {
    ScavTrap::attack(target); // Use ScavTrap's attack version
}