#include "Karen.hpp"

Karen::Karen(void)
{
	std::cout	<< "Karen arrived!\n";
}

Karen::~Karen(void)
{
	std::cout	<< "Karen left!\n";
}

void	Karen::complain(std::string level)
{
	std::string const level_switch[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	void	(Karen::*f[4])(void) = {&Karen::debug, &Karen::info, &Karen::warning, &Karen::error};

	for (int i = 0; i < 4; i++)
	{
		if (level == level_switch[i])
			(this->*f[i])();
	}
}

void	Karen::debug(void)
{
	std::cout	<< "DEBUG level:\n"
				<< "I love having extra bacon for my "
				<< "7XL-double-cheese-triple-pickle-special-ketchup burger.\n"
				<< "I really do!" << std::endl;
}

void	Karen::info(void)
{
	std::cout	<< "INFO level:\n"
				<< "I cannot believe adding extra bacon costs more money.\n"
				<< "You didn’t put enough bacon in my burger!\n"
				<< "If you did, I wouldn’t be asking for more!" << std::endl;

}

void	Karen::warning(void)
{
	std::cout	<< "WARNING level:\n"
				<< "I think I deserve to have some extra bacon for free.\n"
				<< "I’ve been coming for years whereas you started working "
				<< "here since last month." << std::endl;
}

void	Karen::error(void)
{
	std::cout	<< "ERROR level:\n"
				<< "This is unacceptable! I want to speak to the manager now."
				<< std::endl;
}

    // - Declares a constant array of std::string objects named 'level_switch'.
    // - It holds the four specific string values that Karen recognizes as valid complaint levels.
    // - This array will be used to match the input 'level'.
     // 2. Array of pointers to member functions
   // void    (Karen::*f[4])(void) = {&Karen::debug, &Karen::info, &Karen::warning, &Karen::error};
 // a. 'void (Karen::*f[4])(void)' is the TYPE DECLARATION:
    //    - 'void': The return type of the functions that these pointers will point to.
    //    - '(Karen::* ... )': This is the syntax for a pointer to a MEMBER of the 'Karen' class.
    //                          It specifies that the function belongs to 'Karen'.
    //    - '*f[4]': 'f' is declared as an ARRAY of 4 such pointers.
    //    - '(void)': The parameters of the functions that these pointers will point to (in this case, they take no arguments).
    //
    // b. '= {&Karen::debug, &Karen::info, &Karen::warning, &Karen::error}' is the INITIALIZATION:
    //    - '&Karen::debug': The '&' operator here gets the "address" of the member function 'debug' of the 'Karen' class.
    //    - Each element in the array 'f' is initialized with a pointer to one of Karen's complaint methods (`debug`, `info`, `warning`, `error`).
    //
    // In short: 'f' is an array where each element can "point to" one of Karen's specific complaint methods.
 // 4. Check if the input level matches a known level
               // - 'this': 'complain' is a member function, so it's called on a specific 'Karen' object.
            //           'this' is a pointer to that current 'Karen' object.
            // - '->*': This is the "pointer-to-member" operator. It's used when you have an object pointer (like 'this')
            //          and you want to invoke a member function via a pointer-to-member (like 'f[i]').
            //          It effectively means "call the function pointed to by 'f[i]' ON THE OBJECT pointed to by 'this'".
            // - 'f[i]': This selects the correct member function pointer from the array (e.g., if i is 0, it selects &Karen::debug).
            // - '()': This actually invokes (calls) the function.