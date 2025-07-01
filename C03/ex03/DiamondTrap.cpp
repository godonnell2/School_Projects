#include "DiamondTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>

DiamondTrap::DiamondTrap() : ClapTrap("DefaultDiamondClap"), ScavTrap("DefaultDiamondScav"), FragTrap("DefaultDiamondFrag") {
    diamondName = "Default";
    name = diamondName + "_clap_name";
    hitPoints = FragTrap::hitPoints;
    energyPoints = ScavTrap::energyPoints;
    attackDamage = FragTrap::attackDamage;
    std::cout << "DiamondTrap " << diamondName << " constructed\n";
}

DiamondTrap::DiamondTrap(const std::string& _name) : ClapTrap(_name + "_clap_base_init"), ScavTrap(_name + "_scav_base_init"), FragTrap(_name + "_frag_base_init") {
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
    ScavTrap::attack(target);
}