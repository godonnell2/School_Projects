#include "AForm.hpp"

std::string	AForm::get_name(void)const
{
	return (name);
}

bool	AForm::get_signed_status(void)const
{
	return (is_signed);
}

int	AForm::get_sign_required_grade(void)const
{
	return (sign_required_grade);
}

int	AForm::get_execute_required_grade(void)const
{
	return (execute_required_grade);
}