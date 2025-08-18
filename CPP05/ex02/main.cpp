#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"

int main(void)
{
	ShrubberyCreationForm	form_28b;
	Bureaucrat	mister;

	mister.signForm(form_28b);
	mister.executeForm(form_28b);
	
}

/*
Abstract base classes (ABC) with pure virtual functions
Inheritance & Polymorphism
Concrete derived classes (specialized Forms)
Encapsulation of execution rules

File I/O (in ShrubberyCreationForm)
In ex01, you had a Form that a Bureaucrat could sign.
In ex02, Form becomes AForm, where A = Abstract.a pure virtual function like
This forces all subclasses to implement their own execute() method.

You cannot create an AForm object directly anymore. You must instantiate a subclass.
Concept: abstract base classes let you enforce a common interface, but push details to subclasses.
You implement 3 example forms:Concept: polymorphism in action — one execute() interface, many implementations.
This teaches guard conditions and runtime checks.
gradeToSign (exec only if form signed
gradeToExecute exec only if grade high enough
*/