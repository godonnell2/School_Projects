#ifndef INTERN_HPP
#define INTERN_HPP
#pragma once

#include "AForm.hpp"
#include <iostream>

class Intern
{
private:
	/* data */
public:
	Intern(/* args */);
	Intern(Intern& cpy);
	Intern& operator=(Intern& cpy);
	~Intern();
	AForm*	makeForm(std::string& form_name, std::string& target);
};

Intern::Intern(/* args */)
{
	std::cout << "Intern default constructor called\n";
}

Intern::~Intern()
{
	std::cout << "Intern destructor called\n";
}

Intern::Intern(Intern& cpy)
{
	std::cout << "Intern copy constructor called\n";
	*this = cpy;
}

Intern&	Intern::operator=(Intern& cpy)
{
	std::cout << "Intern copy assignment operator called\n";
	(void)cpy;
	return (*this);
}

AForm*	Intern::makeForm(std::string& form_name, std::string& target)
{
	std::string	forms[] = {"ShrubberyCreationForm", "RobotomyRequestForm", "PresidentialPardonForm"};
	int i = 0;
	while (i < 3 && form_name != forms[i])
		i++;
	
	switch (i)
	{
		case 0:
		{
			std::cout<<"Creating ShrubberyCreationForm"<<std::endl;
			return (new ShrubberyCreationForm(target));
		}
		case 1:
		{
			std::cout<<"Creating RobotomyRequestForm"<<std::endl;
			return (new RobotomyRequestForm(target));
		}
		case 2:
		{
			std::cout<<"Creating PresidentialPardonForm"<<std::endl;
			return (new PresidentialPardonForm(target));
		}
		default:
			std::cout<<"That form doesnt exist"<<std::endl;
			break;
	}
	return (NULL);
}





#endif