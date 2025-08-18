#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat(): name("joe"), grade(100)
{
	std::cout << "bureaucrat default constructor called\n";
}

Bureaucrat::Bureaucrat(Bureaucrat& cpy): name(cpy.get_name()), grade(cpy.get_grade())
{
	std::cout << "bureaucrat cpy constructor called\n";
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "bureaucrat default destructor called\n";
}

int	Bureaucrat::get_grade(void)const
{
	return (grade);
}

std::string Bureaucrat::get_name(void)const
{
	return (name);
}

Bureaucrat& Bureaucrat::operator=(Bureaucrat& cpy)
{
	std::cout << "cpy assignment operator called\n";
	if (this != &cpy)
		this->grade = cpy.grade;
	return (*this);
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("grade too high:<\n");
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("grade too low\n");
}

std::ostream &operator<<(std::ostream & os, Bureaucrat const &bur)
{
	os << bur.get_name() << ", bureaucrat grade " << bur.get_grade() << ".\n";
	return (os);
}

void	Bureaucrat::IncrementGrade(void)
{
	if (grade > 1)
		grade--;
	else
		throw GradeTooHighException();
}

void	Bureaucrat::DecrementGrade(void)
{
	if (grade < 150)
		grade++;
	else
		throw GradeTooLowException();
}

void	Bureaucrat::signForm(Form& form)
{
	try
	{
		form.be_signed(*this);
	}
	catch (const std::exception& ex)
	{
		std::cerr << this << "cant sign the form " << form  << "because " << ex.what();
	}
}