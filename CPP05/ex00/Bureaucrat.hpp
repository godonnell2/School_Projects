#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <exception>

class Bureaucrat
{
private:
	const std::string name; // encapsulated, can’t be modified directly
	int grade;  // encapsulated, only modified in a controlled way
public:
	Bureaucrat();
	Bureaucrat(Bureaucrat& cpy);
	Bureaucrat& operator=(Bureaucrat& cpy);
	~Bureaucrat();
	int			get_grade(void)const;   // getter
	std::string	get_name(void)const; // getter
	void	IncrementGrade(void);  // modifies grade in a safe way
	void	DecrementGrade(void);
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

std::ostream &operator<<(std::ostream & os, Bureaucrat const &bur);

#endif