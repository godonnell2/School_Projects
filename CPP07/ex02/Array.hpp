#ifndef ARRAY_H
# define ARRAY_H

# include <iostream>
# include <exception>

template <typename T>
class Array {

	private:
		T				*data;
		unsigned int	array_size;
	
	public:
		Array();
		Array(unsigned int n);
		~Array();
		Array(const Array &copy);
		Array &operator=(const Array &other);

		T& operator[](unsigned int index);
		unsigned int size() const;

		class IndexOutOfBounds : public std::exception {
            public:
                virtual const char *what() const throw ();
        };
};

# include "Array.tpp"

#endif

