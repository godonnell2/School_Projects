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
You learn: To model relationships where one class depends on another while still respecting encapsulation.
The order of construction (Form before Bureaucrat) and destruction (Bureaucrat before Form) because objects in the same scope are destroyed in reverse order of creation.
Your debug prints confirm who is signing what, and whether it succeeded.
The raw pointer value (0x16d5036e8) is just the memory address of the Form object.
&form means the address of the form in memory.

Since you don’t have an operator<< defined for Form, C++ falls back to printing the pointer value.
*/