#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL)
{
	
}

HumanB::HumanB(std::string name, Weapon * weapon_type) : _name(name), _weapon(weapon_type)
{
	
}

HumanB::~HumanB(void)
{
	
}

void	HumanB::attack(void) const
{
	std::cout << this->_name << " attacks with their ";
	if (_weapon)
		std::cout << _weapon->getType() << std::endl;
	else
		std::cout << "hands\n";
}

void	HumanB::setWeapon(Weapon & weapon_type)
{
	this->_weapon = &weapon_type;
}