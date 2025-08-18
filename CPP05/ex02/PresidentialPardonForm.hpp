#ifndef PresidentialPardonForm_HPP
#define PresidentialPardonForm_HPP
#pragma once

#include "AForm.hpp"
# include <iostream>
# include <string>
# include <exception>

class PresidentialPardonForm : public AForm
{
private:
	std::string target;
public:
	PresidentialPardonForm();
	PresidentialPardonForm(PresidentialPardonForm& cpy);
	PresidentialPardonForm(std::string target);
	~PresidentialPardonForm();
	PresidentialPardonForm& operator=(PresidentialPardonForm& cpy);
	virtual void	executeForm(void)const;
};

#endif