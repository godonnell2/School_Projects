#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP
#pragma once

#include "AForm.hpp"
#include "Bureucrat.hpp"
# include <iostream>
# include <string>
# include <cstring>
# include <math.h>
# include <cmath>
# include <fstream>
# include <exception>

class Bureucrat;

class ShrubberyCreationForm : public AForm
{
private:
	std::string target;
public:
	ShrubberyCreationForm();
	ShrubberyCreationForm(ShrubberyCreationForm& cpy);
	ShrubberyCreationForm(std::string target);
	~ShrubberyCreationForm();
	ShrubberyCreationForm& operator=(ShrubberyCreationForm& cpy);
	virtual void	executeForm(void)const;
	class CouldNotOpenFile : public std::exception
	{
		public :
			virtual const char *what() const throw();
	};
};



#endif