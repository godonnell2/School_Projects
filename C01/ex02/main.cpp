
#include <iostream>
#include <string> 

int	 main(void)
{
	std::string	my_var = "HI THIS IS BRAIN";
	std::string	*stringPTR = &my_var;
	std::string	&stringREF = my_var;

	std::cout << std::endl;
	std::cout << "The memory address of string my_var   = " << &my_var << std::endl;
	std::cout << "The memory address held by *stringPTR = " << stringPTR << std::endl;
	std::cout << "The memory address held by &stringREF = " << &stringREF << std::endl;
	std::cout << std::endl;
	std::cout << "The value of the string my_var     = " << my_var << std::endl;
	std::cout << "The value pointed to by *stringPTR = " << *stringPTR << std::endl;
	std::cout << "The value pointed to by &stringREF = " << stringREF << std::endl;
	std::cout << std::endl;
	
	my_var = "everything new this time!";
	std::cout << "The value of the string my_var     = " << my_var << std::endl;
	std::cout << "The value pointed to by *stringPTR = " << *stringPTR << std::endl;
	std::cout << "The value pointed to by &stringREF = " << stringREF << std::endl;
	std::cout << std::endl;
	return (0);
}

    // This declares a variable named 'my_var' of type std::string (a string object from the standard library)
    // and initializes it with the literal string "HI THIS IS BRAIN".
    // 'my_var' directly holds the string data.
    //stringPTR' now holds the memory address of 'my_var'. It "points to" my_var.
    //This declares a REFERENCE variable named 'stringREF'.
    // - 'std::string &': The ampersand (&) here indicates that 'stringREF' is a reference.
    //                    A reference is essentially an ALIAS or another name for an existing variable.
    // - '= my_var': A reference MUST be initialized when it's declared, and it cannot be re-assigned
    //                to refer to a different variable later.
    // So, 'stringREF' now acts as another name for 'my_var'. Any operation on 'stringREF'
    // is actually performed on 'my_var'. BASICALLY IS A PTR BUT ALWAYS HAS A VALUE, AND IMPLICITLY CONVERTIBLE