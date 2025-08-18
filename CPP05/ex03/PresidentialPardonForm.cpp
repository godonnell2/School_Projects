#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardonForm", 25, 5), target("joe")
{
	std::cout << "Presidential pardon form default constructor called\n";
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm& cpy) : AForm(cpy)
{
	std::cout << "PresidentialPardonForm copy constructor called\n";
	*this = cpy;
}

PresidentialPardonForm::PresidentialPardonForm(std::string ttarget) : AForm("PresidentialPardonForm", 25, 5), target(ttarget)
{
	std::cout << "Presidential pardon form target constructor called\n";
}

PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << "presidential pardon form destructor called\n";
}

PresidentialPardonForm& PresidentialPardonForm::operator=(PresidentialPardonForm& cpy)
{
	std::cout << "Presidential pardon opeRAtoR ovERlAod clade\n";
	if (this != &cpy)
	{
		target = cpy.target;
	}
	return (*this);
}

void	PresidentialPardonForm::executeForm(void)const
{
	std::cout << target << "has been pardoned by Zaphod Beeblebrox\n";
}
