#ifndef ZOMBIE_H
# define ZOMBIE_H
# include <iostream>

class Zombie
{

public:
 // Constructors and Destructors
	Zombie(void); // Default Constructor
	~Zombie(void); // Destructor

	 // Member Functions
	void	announce( void );
     // Function to create a horde of zombies
	Zombie* zombieHorde( int N, std::string name );

private:

	std::string	_name; // Private member variable to store the zombie's name
};

#endif