/*
goal to understand constructors, destructors and member fucntions
and instantiation
*/

#include <iostream>
#include "megaphone.hpp"

Zombie::Zombie(std::string name) : _name(name) {}

Zombie::~Zombie() 
{
    std::cout << _name << " is destroyed." << std::endl;
}

void Zombie::announce() const 
{
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

/*
When created, it stores a name

When announce() is called, it prints a zombie-like message

When destroyed (goes out of scope or is deleted), it prints a destruction message
*/


int main() {
    Zombie z1("Zed");
    z1.announce();

    {
        Zombie z2("Zoey");
        z2.announce();
    } 

    return 0;
}

/*
Stack-based instantiation (Zombie z1)

The announce() method being called

z2 being destroyed automatically when going out of scope (you'll see its destructor message)
*/