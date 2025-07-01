#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>
#include <iostream>

class ClapTrap {
private:
    std::string name;
    int hitPoints;
    int energyPoints;
    int attackDamage;

public:
    ClapTrap(std::string _name);
    ~ClapTrap();

    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
};

#endif

/*
Benefit 1 (Efficiency): Instead of making a complete copy of the std::string object (which could be large) 
when the function is called, the function receives a direct "alias" or "link" to the original std::string object. This avoids the overhead of copying.
Benefit 2 (Avoiding copies): It's common practice for passing objects.
 If you didn't use a reference (or a pointer), it would be called pass-by-value, and it would indeed make a copy of the string.
Here's how that function signature would look and how it would work:
Function Signature (Pass-by-Value):
void attack(std::string target); // No '&'
*/