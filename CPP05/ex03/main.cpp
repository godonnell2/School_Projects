#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "Intern.hpp"

int main(void)
{
	Bureaucrat	mister;
	Intern		grub;

	std::string target("home");
	std::string form_name("ShrubberyCreationForm");

	AForm *trees = grub.makeForm(form_name, target);

	mister.signForm(*trees);
	mister.executeForm(*trees);

	delete trees;
}

/*
Intern is a new class .
Its job is to create forms dynamically.
You don’t call new ShrubberyCreationForm directly in main; instead, you ask the intern to make it.
The intern uses strings to decide which subclass to instantiate:

"shrubbery creation" → ShrubberyCreationForm
"robotomy request" → RobotomyRequestForm
"presidential pardon" → PresidentialPardonForm
Concept: Factory pattern — abstract object creation into a helper class.

The intern returns a pointer to the base class AForm.
At runtime, the actual derived class (ShrubberyCreationForm) is stored in the base pointer.
This allows you to interact with forms uniformly (through the base class interface), while the actual behavior is determined by the derived type.
*/