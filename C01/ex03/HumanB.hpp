#ifndef HUMANB_H
# define HUMANB_H
# include "Weapon.hpp"
# include <iostream>

class HumanB
{

public:

	HumanB(std::string name);
	HumanB(std::string name, Weapon * weapon_type);
	~HumanB(void);

	void		attack(void) const;
	void		setWeapon(Weapon & weapon_type);
	
private:

	std::string	_name;
	Weapon		*_weapon;
	
};
