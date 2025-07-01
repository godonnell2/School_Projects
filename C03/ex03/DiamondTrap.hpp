#pragma once
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap {
private:
    std::string diamondName;

public:
    DiamondTrap();
    DiamondTrap(const std::string& name);
    ~DiamondTrap();

    void whoAmI();
    void attack(const std::string& target); // Use ScavTrap's attack
};