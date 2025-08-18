#ifndef ITER_H
# define ITER_H

# include <iostream>
# include <string>

template<typename T, typename U, typename V>
void	iter(T addr, U len, V func) {
	for (U i = 0; i < len; i++) {
		func(addr[i]);
	}
}

template<typename T>
void	print(T arg) {
	std::cout << arg << std::endl;
}

#endif