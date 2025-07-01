#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string _name)
    : name(_name), hitPoints(10), energyPoints(10), attackDamage(0) {
    std::cout << "ClapTrap " << name << " constructed\n";
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap " << name << " destructed\n";
}

void ClapTrap::attack(const std::string& target) {
    if (energyPoints <= 0 || hitPoints <= 0) {
        std::cout << "ClapTrap " << name << " can't attack\n";
        return;
    }
    energyPoints--;
    std::cout << "ClapTrap " << name << " attacks " << target
              << ", causing " << attackDamage << " points of damage!\n";
}

void ClapTrap::takeDamage(unsigned int amount) {
    hitPoints -= amount;
    if (hitPoints < 0)
        hitPoints = 0;
    std::cout << "ClapTrap " << name << " takes " << amount
              << " points of damage! Remaining HP: " << hitPoints << "\n";
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (energyPoints <= 0 || hitPoints <= 0) {
        std::cout << "ClapTrap " << name << " can't be repaired\n";
        return;
    }
    energyPoints--;
    hitPoints += amount;
    std::cout << "ClapTrap " << name << " repairs itself for " << amount
              << " HP! New HP: " << hitPoints << "\n";
}

/*
attack - consumes one energypt (if can attack)
take damage - hitpts removes one btu dont go below 0
be repaired -unsigned int to ensure it never goes negative consumes one ept adds one hitpt
*/