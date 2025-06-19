#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
	{
	Weapon club = Weapon("crude spiked club");
	HumanA Mother_Teresa("Mother Teresa", club);
	Mother_Teresa.attack();
	club.setType("some other type of club");
	Mother_Teresa.attack();
	}
	{
	Weapon club = Weapon("crude spiked club");
	HumanB jim("Jim");
	jim.attack();
	jim.setWeapon(club);
	jim.attack();
	club.setType("heavy club");
	jim.attack();
	}
	return 0;
}

/*

1. Weapon Class
Purpose: Represents a weapon with a specific type (e.g., "sword", "club").
Constructor (Weapon(std::string type)): Initializes the weapon's type.
Destructor (~Weapon(void)): (Empty) handles cleanup when a weapon object is destroyed.
getType(): Returns the weapon's type.
setType(std::string newType): Changes the weapon's type.
_type (private): Stores the weapon's name.
2. HumanA Class
Key Feature: It always has a weapon because it takes a Weapon & weapon_type (a reference) in its constructor. A reference must refer to an existing object and cannot be changed to refer to another object later.
Constructor (HumanA(std::string name, Weapon & weapon_type)): Initializes the human's name and directly binds to an existing Weapon object using a reference (_weapon).
attack(): Prints that the human attacks with their weapon's type. Since _weapon is a reference, any change to the original Weapon object it refers to will be reflected when HumanA attacks.
3. HumanB Class
Key Feature: It might not have a weapon initially, or its weapon can be changed later, because it uses a Weapon * _weapon (a pointer). A pointer can be NULL (point to nothing) or be reassigned to point to different Weapon objects.
Constructors:
HumanB(std::string name): Initializes with a name, but no weapon (_weapon is NULL).
HumanB(std::string name, Weapon * weapon_type): Initializes with a name and a pointer to a weapon.
setWeapon(Weapon & weapon_type): Allows you to give HumanB a weapon after it's been created, by setting its _weapon pointer to the address of an existing Weapon object.
attack(): Checks if _weapon is pointing to a valid weapon (if (_weapon)). If so, it uses that weapon's type; otherwise, it says they attack with "hands".
4. main() Function
The main function demonstrates the different behaviors:

First Block (HumanA):

A Weapon club is created.
Mother_Teresa (HumanA) is created and immediately bound to club.
When club's type is changed, Mother_Teresa's subsequent attack() reflects this change because HumanA holds a reference to the original club object.
Second Block (HumanB):

Another Weapon club is created.
jim (HumanB) is created without a weapon initially. His first attack is with "hands".
jim.setWeapon(club): jim is then given the club weapon.
Subsequent attacks use the club. When club's type is changed, jim's later attack() also reflects this, as HumanB holds a pointer to the original club object.
*/