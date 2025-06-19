/*
goal to understand constructors, destructors and member fucntions
and instantiation
*/

#include <iostream>
#include "zombie.hpp"

Zombie::Zombie(std::string name) : _name(name) {}
/*
alternative with this 
Zombie::Zombie(std::string name)
{
	this->_name = name;
}

*/

Zombie::~Zombie() 
{
    std::cout << _name << " is destroyed." << std::endl;
}

void Zombie::announce() const 
{
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

/*

Zombie::: This is the scope resolution operator. It tells the compiler
 that the function being defined (Zombie) belongs to the Zombie class.
 Zombie(std::string name): This is the constructor itself.
A constructor is a special member function that has the same name as the class.
It's called automatically when an object of the Zombie class is created.
When a Zombie object is created with a given name (e.g., Zombie myZombie("Brains");), first, take that name and use it directly to initialize the _name member variable of this new Zombie object. 
After that, there's nothing more to do within the constructor's main body."
It takes one argument, std::string name, which is the name you want to give to this specific Zombie object.
: (Colon):

This colon signifies the start of the initializer list.
Everything between the colon and the opening curly brace { is part of this list.
This is an entry in the initializer list.
_name: This refers to the member variable of your Zombie class (declared as std::string _name;).
When created, it stores a name

When announce() is called, it prints a zombie-like message

When destroyed (goes out of scope or is deleted), it prints a destruction message
*/


