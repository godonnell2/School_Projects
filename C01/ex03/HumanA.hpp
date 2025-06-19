#ifndef HUMANA_H
# define HUMANA_H
# include "Weapon.hpp"
# include <iostream>

class HumanA
{

public:

	HumanA(std::string name, Weapon & weapon_type);
	~HumanA(void);

	void		attack(void) const;

private:

	std::string	_name;
	Weapon		&_weapon;
};

#endif