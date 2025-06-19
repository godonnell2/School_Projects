#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon & weapon_type) : _name(name), _weapon(weapon_type)
{
	
}

HumanA::~HumanA(void)
{
	
}

void	HumanA::attack(void) const
{
	std::cout << this->_name << " attacks with their " << _weapon.getType() << std::endl;
}