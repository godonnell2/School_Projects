#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	(void)av;

	try {
		if(ac > 1)
		{
			PmergeMe Merge(av);

			Merge.display();
		}
		else
			throw std::runtime_error("Error");
	} catch (std::exception &e){
		std::cerr << e.what() << std::endl;
	}
}