#include "Bureaucrat.hpp"

int main(void)
{
	Bureaucrat a;
	std::cout << a; //print name + grade

	for (int i = 0 ; i < 51 ; i++)
	{
		try
		{
			std::cout << "attempting to decrement grade\n";
			a.DecrementGrade();
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what();
		}
	}
}

/*
implement bureau class
-has a name (constant, cannot change).
-Has a grade (1 = highest, 150 = lowest).
Enforce grade rules:
-Throw GradeTooHighException if < 1.
-Throw GradeTooLowException if > 150.
Implement incrementGrade() and decrementGrade(), which also enforce rules.
Overload << to print Bureaucrat’s details.
Encapsulation means keeping the internal state of an object protected and controlled.
An invariant is a condition that must always be true for the object to remain valid.
For Bureaucrat:
The grade must always be between 1 (highest) and 150 (lowest).
together they make the class robust

Every call to DecrementGrade() makes the grade increase by +1 (since lower rank = higher number, e.g. 1 = best, 150 = worst).

Without exceptions, your grade could become invalid (e.g. 151).

With exceptions, the catch block handles the invalid operation gracefully → 
printing "grade too low" instead of letting the program crash or corrupt data.

The base class std::exception has a virtual method called .what() that returns a C-style string (const char*) describing the error.
*/