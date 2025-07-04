#include "DiamondTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>

DiamondTrap::DiamondTrap() : ClapTrap("DefaultDiamondClap"), ScavTrap("DefaultDiamondScav"), FragTrap("DefaultDiamondFrag") {
    diamondName = "Default";
    _name = diamondName + "_clap_name";
    _hitPoints = FragTrap::_hitPoints;
    _energyPoints = ScavTrap::_energyPoints;
    _attackDamage = FragTrap::_attackDamage;
    std::cout << "DiamondTrap " << diamondName << " constructed\n";
}

DiamondTrap::DiamondTrap(const std::string& name_param) 
    : ClapTrap(name_param + "_clap_name"),
      ScavTrap(name_param), 
      FragTrap(name_param), 
      diamondName(name_param)
{
    
    this->_hitPoints = 100;      
    this->_energyPoints = 50;   
    this->_attackDamage = 30;    

    std::cout << "DiamondTrap " << diamondName << " constructed\n";
}

DiamondTrap::~DiamondTrap() {
    std::cout << "DiamondTrap " << diamondName << " destructed\n";
}

void DiamondTrap::whoAmI() {
    std::cout << "I am " << diamondName << ", and my ClapTrap name is " << _name << "\n";
}

void DiamondTrap::attack(const std::string& target) {
    ScavTrap::attack(target);
}