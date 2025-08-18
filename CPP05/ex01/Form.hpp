#ifndef FORM_HPP
#define FORM_HPP
#pragma once

# include <iostream>
# include <exception>
# include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
private:
	const std::string name;
	bool	is_signed;
	const int	sign_required_grade;
	const int	execute_required_grade;
public:
	Form();
	Form(Form& cpy);
	Form& operator=(Form& cpy);
	~Form();
	std::string	get_name(void)const;
	bool		get_signed_status(void)const;
	int			get_sign_required_grade(void)const;
	int			get_execute_required_grade(void)const;
	void		be_signed(Bureaucrat& signer);
	class GradeToLowToSign : public std::exception
	{
		public:
			const char	*err(void)const throw(); 
	};
	class GradeTooHighException : public std::exception
	{
		public :
			virtual const char *what() const throw();
	};
	class GradeTooLowException : public std::exception
	{
		public :
			virtual const char *what() const throw();
	};
};

std::ostream &operator<<(std::ostream & os, Form const &form);

#endif