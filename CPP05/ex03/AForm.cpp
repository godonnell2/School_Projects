#include "AForm.hpp"

AForm::AForm(/* args */): name("AformA1"), is_signed(false), sign_required_grade(100), execute_required_grade(100)
{
	std::cout << "Aform default constructor called\n";
}

AForm::AForm(AForm& cpy): name(cpy.name), is_signed(cpy.is_signed), sign_required_grade(cpy.sign_required_grade), execute_required_grade(cpy.execute_required_grade)
{
	std::cout << "AForm copy constructor called\n";
}

AForm::AForm(std::string nname, int sign_grade, int exec_grade): name(nname), is_signed(false), sign_required_grade(sign_grade), execute_required_grade(exec_grade)
{
	std::cout << "Aform full constructor called\n";
}

AForm::~AForm()
{
}

AForm&	AForm::operator=(AForm& cpy)
{
	if (this != &cpy)
		is_signed = cpy.get_signed_status();
	return (*this);
}

std::ostream &operator<<(std::ostream & os, AForm const &Aform)
{
	os << "Aform: " << Aform.get_name() << (Aform.get_signed_status() ? " is signed" : " isnt signed") << " requires: " << Aform.get_sign_required_grade() << " to be signed, and: " << Aform.get_execute_required_grade() << " to be executed\n";
	return (os);
}

void	AForm::be_signed(Bureucrat& signer)
{
	std::cout << signer << "is trying to sign " << this;
	if (signer.get_grade() > sign_required_grade)
		throw (GradeToLowToSign());
	else
	{
		std::cout << "\nthe Aform signed succesfuly\n";
		is_signed = 1;
	}
}

void	AForm::execute(Bureucrat const & executor)const
{
	if (!is_signed)
		throw FormNotSignedException();
	else if (executor.get_grade() > execute_required_grade)
		throw GradeTooLowException();
	else
		executeForm();
}
