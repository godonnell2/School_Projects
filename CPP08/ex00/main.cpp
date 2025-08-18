#include "easyfind.hpp"

int main()
{
	std::vector<int> vec = {1, 2, 3, 4, 5};

	try {
		auto it = easyfind(vec, 3);
		std::cout << "Found value: " << *it << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::list<int> lst = {10, 20, 30, 40};
    try {
        auto it = easyfind(lst, 25);
        std::cout << "Found value: " << *it << std::endl;
    }
	catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}	
