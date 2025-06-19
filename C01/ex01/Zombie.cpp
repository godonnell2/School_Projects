#include "Zombie.hpp"

// The body is empty.
// This means the private member _name will be default-constructed (initialized to an empty string).
Zombie::Zombie(void)
{

}

//prints when deconstructor called and name
Zombie::~Zombie(void)
{
	std::cout << "Deconstructor called -> " << this->_name << std::endl;
}

void	Zombie::announce(void)
{
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ...\n";
}