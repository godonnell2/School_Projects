#ifndef BUREUCRAT_HPP
#define BUREACRAT_HPP
#pragma once

#include "AForm.hpp"
#include <iostream>
#include <exception>

class AForm;

class Bureucrat
{
private:
	const std::string name;
	int grade;
public:
	Bureucrat();
	Bureucrat(Bureucrat& cpy);
	Bureucrat& operator=(Bureucrat& cpy);
	~Bureucrat();
	int			get_grade(void)const;
	std::string	get_name(void)const;
	void	IncrementGrade(void);
	void	DecrementGrade(void);
	void	signForm(AForm& ola);
	void	executeForm(AForm const &form);
	class GradeTooHighException : public std::exception
	{
		public :
			virtual const char *what() const throw();
	};
	class GradeTooLowException : public std::exception
	{
		public :
			virtual const char *what() const throw();
	};
};

std::ostream &operator<<(std::ostream & os, Bureucrat const &bur);


#endif