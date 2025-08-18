#include "Form.hpp"

Form::Form(/* args */): name("formA1"), is_signed(false), sign_required_grade(100), execute_required_grade(100)
{
	std::cout << "form default constructor called\n";
}

Form::Form(Form& cpy): name(cpy.name), is_signed(cpy.is_signed), sign_required_grade(cpy.sign_required_grade), execute_required_grade(cpy.execute_required_grade)
{
	std::cout << "Form copy constructor called\n";
}

Form::~Form()
{
}

Form&	Form::operator=(Form& cpy)
{
	if (this != &cpy)
		is_signed = cpy.get_signed_status();
	return (*this);
}

std::ostream &operator<<(std::ostream & os, Form const &form)
{
	os << "form: " << form.get_name() << (form.get_signed_status() ? " is signed" : " isnt signed") << " requires: " << form.get_sign_required_grade() << " to be signed, and: " << form.get_execute_required_grade() << " to be executed\n";
	return (os);
}

void	Form::be_signed(Bureaucrat& signer)
{
	std::cout << signer << "is trying to sign " << this;
	if (signer.get_grade() > sign_required_grade)
		throw (GradeToLowToSign());
	else
	{
		std::cout << "\nthe form signed succesfuly\n";
		is_signed = 1;
	}
}

