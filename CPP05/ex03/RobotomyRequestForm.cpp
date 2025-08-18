#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45), target("joe")
{
	std::cout << "Robotomy request form default constructor called\n";
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm& cpy): AForm(cpy)
{
	std::cout << "RobotomyRequestForm copy constructor called\n";
	*this = cpy;
}

RobotomyRequestForm::RobotomyRequestForm(std::string ttarget) : AForm("RobotomyRequestForm", 72, 45), target(ttarget)
{
	std::cout << "Robotomy request form target constructor called\n";
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << "Robotomy request form destructor called\n";
}

RobotomyRequestForm& RobotomyRequestForm::operator=(RobotomyRequestForm& cpy)
{
	std::cout << "Robotomy request form opeRAtoR ovERlAod clade\n";
	if (this != &cpy)
	{
		target = cpy.target;
	}
	return (*this);
}

void	RobotomyRequestForm::executeForm(void)const
{
	int success = rand() % 2;
	std::cout << "I the robot doktor will now demonstrate a leading treatment in robot mental health\n";
	if (success)
		std::cout << "behold " << target << " is now ROBotomized!\n";
	else
		throw FailedRobotomy();
}

const char *RobotomyRequestForm::FailedRobotomy::what() const throw()
{
	return ("The robotomy was unsucessfull:(\n");
}
