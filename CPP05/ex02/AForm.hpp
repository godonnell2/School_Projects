#ifndef AFORM_HPP
#define AFORM_HPP
#pragma once

# include <iostream>
# include <exception>
# include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
private:
	const std::string name;
	bool	is_signed;
	const int	sign_required_grade;
	const int	execute_required_grade;
public:
	AForm();
	AForm(std::string nname, int sign_grade, int exec_grade);
	AForm(AForm& cpy);
	AForm&		operator=(AForm& cpy);
	virtual 	~AForm() = 0;
	std::string	get_name(void)const;
	bool		get_signed_status(void)const;
	int			get_sign_required_grade(void)const;
	int			get_execute_required_grade(void)const;
	void		be_signed(Bureaucrat& signer);
	void		execute(Bureaucrat const & executor)const;
	virtual void	executeForm(void)const = 0;
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
	class FormNotSignedException : public std::exception
	{
		public :
			virtual const char *what() const throw();
	};
};

std::ostream &operator<<(std::ostream & os, AForm const &Aform);

#endif