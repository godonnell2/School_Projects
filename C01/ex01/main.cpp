
#include <iostream>
#include "Zombie.hpp"

int	main(void)
{
	Zombie	*new_horde = NULL;

	new_horde = new_horde->zombieHorde(15, "Gail");
	for (int i = 0; i < 15; i++)
	{
		std::cout << "Nb. " << i << std::endl;
		new_horde[i].announce();
	}
	delete [] new_horde;
    new_horde = NULL;
	return (0);
}

//When delete [] is called on an array of objects, 
// it ensures that the destructor (~Zombie(void)) is called for each object in the array (15 times in this case) before the memory for the entire array is deallocated.