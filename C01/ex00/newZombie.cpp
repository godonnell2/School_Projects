#include "zombie.hpp"

Zombie* Zombie::newZombie( std::string name )
{
	Zombie *new_zombie = new Zombie(name);
	return (new_zombie);
}

/*
we are returning the ptr cos that+s what needs to come out of the fn
*/