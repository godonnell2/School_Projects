#include "Bureucrat.hpp"
#include "Form.hpp"

Bureucrat::Bureucrat(): name("joe"), grade(100)
{
	std::cout << "bureacrat default constructor called\n";
}

Bureucrat::Bureucrat(Bureucrat& cpy): name(cpy.get_name()), grade(cpy.get_grade())
{
	std::cout << "bureacrat cpy constructor called\n";
}

Bureucrat::~Bureucrat()
{
	std::cout << "bureacrat default destructor called\n";
}

int	Bureucrat::get_grade(void)const
{
	return (grade);
}

std::string Bureucrat::get_name(void)const
{
	return (name);
}

Bureucrat& Bureucrat::operator=(Bureucrat& cpy)
{
	std::cout << "cpy assignment operator called\n";
	if (this != &cpy)
		this->grade = cpy.grade;
	return (*this);
}

const char *Bureucrat::GradeTooHighException::what() const throw()
{
	return ("grade too high:<\n");
}

const char *Bureucrat::GradeTooLowException::what() const throw()
{
	return ("grade too low\n");
}

std::ostream &operator<<(std::ostream & os, Bureucrat const &bur)
{
	os << bur.get_name() << ", bureaucrat grade " << bur.get_grade() << ".\n";
	return (os);
}

void	Bureucrat::IncrementGrade(void)
{
	if (grade > 1)
		grade--;
	else
		throw GradeTooHighException();
}

void	Bureucrat::DecrementGrade(void)
{
	if (grade < 150)
		grade++;
	else
		throw GradeTooLowException();
}


void	Bureucrat::signForm(Form& form)
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