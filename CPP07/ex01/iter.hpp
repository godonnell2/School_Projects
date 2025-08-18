#pragma once

# include <iostream>
# include <string>
# include <cstring>
# include <cmath>
# include <fstream>

template <typename T, typename F> void iter(T* array, size_t len, F f)
{
	T* helper_ptr = array;
	if (!array || !f)
		return ;
	for (size_t i = 0; i < len; i++)
	{
		if (!(helper_ptr + i))
		{
			std::cout << "you are being naughty on purpose\n";
			return ;
		}
		f(*(helper_ptr + i));
	}
}