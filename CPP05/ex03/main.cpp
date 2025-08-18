#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "Intern.hpp"

int main(void)
{
	Bureucrat	mister;
	Intern		grub;

	std::string target("home");
	std::string form_name("ShrubberyCreationForm");

	AForm *trees = grub.makeForm(form_name, target);

	mister.signForm(*trees);
	mister.executeForm(*trees);

	delete trees;
}