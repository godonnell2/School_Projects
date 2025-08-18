#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
	Form	form_28b;
	Bureaucrat	mister;

	mister.signForm(form_28b);

	
}

/*
Interaction between classes.

Composition (Form has requirements for Bureaucrat).

Encapsulation + validation across multiple classes.

🛠️ What you do:

Add a Form class.

Has name, isSigned, signGrade, execGrade.

Throw exceptions if grades are invalid (<1 or >150).

Bureaucrats can signForm(Form&).

Works only if Bureaucrat’s grade <= signGrade.

Otherwise throw exception.

👉 You learn: To model relationships where one class depends on another while still respecting encapsulation.
*/