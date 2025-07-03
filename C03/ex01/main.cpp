#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
   // Test construction chaining
	// The derived class builds "on top of" the base class.
	// The base must exist before extending it.
	std::cout << "\n=== Constructing ===" << std::endl;
	ScavTrap scav1("SCAV-1");

	// Test functionality
	std::cout << "\n=== Testing ===" << std::endl;
	scav1.attack("Target");
	scav1.guardGate();
	scav1.takeDamage(30);
	scav1.beRepaired(10);

	// Test copy and assignment
	std::cout << "\n=== Copying ===" << std::endl;
	ScavTrap scav2(scav1);
	ScavTrap scav3("scav3");
	scav3 = scav2;

	// Test destruction chaining
	// The derived class may depend on base class resources during cleanup.
	// Destroying the base first would leave the derived class with dangling references.
	std::cout << "\n=== Destructing ===" << std::endl;
	return 0;
}
/*
 First, the base class (ClapTrap) constructor runs
Then, the derived class (ScavTrap) constructor runs both to create scav 1
attack() (probably overridden in ScavTrap)
guardGate() (a new method only ScavTrap has)
takeDamage() and beRepaired() (inherited from ClapTrap)
Concept	Why It Matters
Inheritance	ScavTrap reuses and extends ClapTrap
Canonical Form	Ensures safe copy/assignment/destruction
Copying part	Required — verifies your child class handles it right
guardGate() method	A new feature unique to ScavTrap
Line of Code	Output Line	Why It Happens
ScavTrap scav2(scav1);	ClapTrap copy constructor called	ScavTrap calls base class copy constructor (ClapTrap(const&))
ScavTrap copy constructor called	Then ScavTrap’s own copy constructor
ScavTrap scav3("scav3");	ClapTrap scav3 constructed	Calls ClapTrap's string constructor
ScavTrap scav3 constructor called	Then ScavTrap's string constructor
scav3 = scav2;	ScavTrap copy assignment called	Assignment operator of ScavTrap runs
(inside it...)	ClapTrap copy assignment operator called	Base class assignment operator is called from inside
*/