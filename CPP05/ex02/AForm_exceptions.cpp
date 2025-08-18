#include "AForm.hpp"

const char *AForm::GradeToLowToSign::err() const throw()
{
	return ("grade too low to sign\n");
}

const char *AForm::GradeTooHighException::what() const throw()
{
	return ("grade too high\n");
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return ("grade too low\n");
}

const char *AForm::FormNotSignedException::what() const throw()
{
	return ("Form is not signed:(\n");
}
