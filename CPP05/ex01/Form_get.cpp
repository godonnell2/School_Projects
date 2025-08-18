#include "Form.hpp"

std::string	Form::get_name(void)const
{
	return (name);
}

bool	Form::get_signed_status(void)const
{
	return (is_signed);
}

int	Form::get_sign_required_grade(void)const
{
	return (sign_required_grade);
}

int	Form::get_execute_required_grade(void)const
{
	return (execute_required_grade);
}