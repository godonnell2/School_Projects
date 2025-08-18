#include "iter.hpp"

void	ft_add_one(int &nb)
{
	nb++;
}

int main(void)
{
	int nb[10] = {1,2,3,4,5,6};
	std::cout << nb[0] << "\n";
	std::cout << nb[1] << "\n";
	std::cout << nb[2] << "\n";
	std::cout << nb[3] << "\n";
	std::cout << nb[4] << "\n";
	std::cout << nb[5] << "\n";
	::iter(nb, 6, ft_add_one);
	std::cout << nb[0] << "\n";
	std::cout << nb[1] << "\n";
	std::cout << nb[2] << "\n";
	std::cout << nb[3] << "\n";
	std::cout << nb[4] << "\n";
	std::cout << nb[5] << "\n";
}