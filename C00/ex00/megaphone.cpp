#include <iostream>
#include <cctype>

int main(int ac, char** av) 
{
    if (ac == 1) 
    {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
    } 
    else 
    {
        for (int i = 1; i < ac; ++i) 
        {
            for (int j = 0; av[i][j]; ++j) 
            {
                std::cout << (char)std::toupper(av[i][j]);
            }
        }
        std::cout << std::endl;
    }
    return 0;
}

/*
std::cout << std::endl;
cout == char output like printf
std::endl;
is a special object, called a stream manipulator.
it Prints a newline character (like '\n')
and Flushes the stream buffer (forces the output to appear immediately)
Print a newline to standard output, and then flush the output buffer."
std::cout << "hello"; NO NEWLINE
std::cout << "hello\n";         // ✔ Newline with escape char
std::cout << "hello" << '\n';   // ✔ Same
'\n'	Just adds a newline	Faster, better for performance-critical code
std::endl	Use when you need immediate output (e.g. logs, debug info)
<< send to

*/