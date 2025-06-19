#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie
{
    
public:
    Zombie(std::string name);
    ~Zombie(void);

    void	announce( void ) const;
	Zombie*	newZombie( std::string name );
	void	randomChump( std::string name );

private:

	std::string	_name;
};

/*
private:
    Zombie(std::string name);
defines a constructor.

Zombie: This is the name of the class itself. A function with the same name as the class is a constructor.
(std::string name): This indicates that the constructor takes one argument: a string,
 which will be used to initialize the zombie's name.

 defines a destructor.

~Zombie: The ~ symbol followed by the class name signifies a destructor.
(void): It takes no arguments.

void	announce( void ) const; const means its read only

Zombie*	newZombie( std::string name ); dynamic on heap 
void	randomChump( std::string name ); stack 
*/

#endif