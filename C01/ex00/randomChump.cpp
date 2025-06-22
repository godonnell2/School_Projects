#include "Zombie.hpp"

void Zombie::randomChump(std :: string name)
{
    Zombie new_zombie(name);
    new_zombie.announce();
}

/*
STACK
Lifetime: The Zombie object created by randomChump lives only for the duration of the randomChump function call. It's temporary.
new_zombie is a VARIABLE NAME.
Zombie(name) is the constructor call that initializes that variable.
*/