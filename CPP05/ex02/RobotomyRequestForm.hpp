#ifndef RobotomyRequestForm_HPP
#define RobotomyRequestForm_HPP
#pragma once

#include "AForm.hpp"
# include <iostream>
# include <string>
# include <cstring>
# include <math.h>
# include <cmath>
# include <fstream>
# include <exception>

class RobotomyRequestForm : public AForm
{
private:
	std::string target;
public:
	RobotomyRequestForm();
	RobotomyRequestForm(RobotomyRequestForm& cpy);
	RobotomyRequestForm(std::string target);
	~RobotomyRequestForm();
	RobotomyRequestForm& operator=(RobotomyRequestForm& cpy);
	virtual void	executeForm(void)const;
	class FailedRobotomy : public std::exception
	{
		public :
			virtual const char *what() const throw();
	};
};

#endif