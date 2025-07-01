#include "ScavTrap.hpp"

ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name)  {
    hitPoints = 100;
    energyPoints = 50;
    attackDamage = 20;
    std::cout << "ScavTrap " << name << " constructed with unique identity!\n";
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap " << name << " destructed dramatically.\n";
}

void ScavTrap::attack(const std::string& target) {
    if (energyPoints <= 0 || hitPoints <= 0) {
        std::cout << "ScavTrap " << name << " has no energy to attack!\n";
        return;
    }
    energyPoints--;
    std::cout << "ScavTrap " << name << " aggressively attacks " << target
              << ", dealing " << attackDamage << " points of damage!\n";
}