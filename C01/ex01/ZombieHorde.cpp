
#include "Zombie.hpp"

Zombie* Zombie::zombieHorde( int N, std::string name )
{
	Zombie	*horde = NULL;

	if (N <= 0)
		return (NULL);
	horde = new Zombie[N];
	for (int i = 0; i < N; i++)
	{
		horde[i]._name = name;
	}
	return (horde);
}
// Allocate an array of N Zombie objects on the heap.
 // This calls the default constructor (Zombie::Zombie(void)) N times.
// Assign the given name to each zombie in the horde.
// Note: The zombies were first default-constructed with empty names,
        // then their names are reassigned here.
        // Return the pointer to the first zombie in the array.
                               