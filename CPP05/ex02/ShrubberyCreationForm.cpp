#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137), target("Home")
{
	std::cout << "shruberycreationform default constructor called\n";
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm& cpy): AForm(cpy)
{
	std::cout << "ShrubberyCreationForm copy constructor called\n";
	*this = cpy;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string ttarget) : AForm("ShrubberyCreationForm", 145, 137), target(ttarget)
{
	std::cout << "shrubery form creation form target constructor called\n";
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "shrub creation form destructor called\n";
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(ShrubberyCreationForm& cpy)
{
	std::cout << "SHruBeries crEatIon FRom opeRAtoR ovERlAod clade\n";
	if (this != &cpy)
	{
		target = cpy.target;
	}
	return (*this);
}

void	ShrubberyCreationForm::executeForm(void)const
{
	std::ofstream	out((target + "_shrubbery").c_str());

	if (!out)
		throw CouldNotOpenFile();
	out << "  ******\n";
	out << " ********\n";
	out << "**********\n";
	out << "**********\n";
	out << " ********\n";
	out << "  ******\n";
	out << "    ||\n";
	out << "    ||\n";
	out << "    ||\n";
	out << "    ||\n";
	out << "  //||\\\\\n";
	out.close();
}

const char *ShrubberyCreationForm::CouldNotOpenFile::what() const throw()
{
	return ("Unable to reach target\n");
}