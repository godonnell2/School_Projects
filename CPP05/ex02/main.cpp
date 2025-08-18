#include "Bureucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"

int main(void)
{
	ShrubberyCreationForm	form_28b;
	Bureucrat	mister;

	mister.signForm(form_28b);
	mister.executeForm(form_28b);
	
}