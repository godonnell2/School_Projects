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
 CL4P-TP is a direct ClapTrap object, it uses its own attackDamage value, 
 which was set to 0 during its construction. cant alter attack cos it only takes a string as arg
 showign that scav is overriding ClapTraps
*/