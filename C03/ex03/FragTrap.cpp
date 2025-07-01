#include "FragTrap.hpp"
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

FragTrap::FragTrap(const std::string& name) : ClapTrap(name) {
    hitPoints = 100;
    energyPoints = 100;
    attackDamage = 30;
    std::cout << "FragTrap " << name << " appears with high energy!\n";
}

FragTrap::~FragTrap() {
    std::cout << "FragTrap " << name << " has exited with a boom.\n";
}

void FragTrap::attack(const std::string& target) {
    if (energyPoints <= 0 || hitPoints <= 0) {
        std::cout << "FragTrap " << name << " is too tired to attack.\n";
        return;
    }
    energyPoints--;
    std::cout << "FragTrap " << name << " launches a huge attack on " << target
              << ", dealing " << attackDamage << " damage!\n";
}

void FragTrap::highFivesGuys() {
    std::cout << "FragTrap " << name << " asks for a high five! ✋\n";
}