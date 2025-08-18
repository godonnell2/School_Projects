#include "Form.hpp"

const char *Form::GradeToLowToSign::err() const throw()
{
	return ("grade to low to sign\n");
}

const char *Form::GradeTooHighException::what() const throw()
{
	return ("grade too high\n");
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("grade too low\n");
}
