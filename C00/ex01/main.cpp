int main() {
    phoneBook book;
    //create an instance of book  class's default constructor is called 
    std::string command;
    // type is string insted of char *

    std::cout << "Welcome to the Awesome PhoneBook. Commands: ADD, SEARCH, EXIT" << std::endl;

    while (true) 
    {
        std::cout << "Enter command: ";
        std::getline(std::cin, command);

        if (command == "ADD")
            book.addContact();
        else if (command == "SEARCH")
            book.searchContacts();
        else if (command == "EXIT")
            break;
        else
            std::cout << "Unknown command." << std::endl;

        if (std::cin.eof()) break;
    }

    return 0;
}

/*
it's common practice in C++ to capitalize class names
<< is like a pipe sned it to there
std::cin.clear();: If input failed, std::cin is in a "bad" state,
 meaning it won't accept further input until its error flags are cleared. 
This line clears those flags, restoring std::cin to a good state.

Think of namespaces as containers or organizational compartments for names (like classes, functions, variables).
They are used to prevent name collisions. Imagine if every library or every programmer used the same names for their components (e.g., everyone had a List class). If you included multiple libraries, the compiler wouldn't know which List you're referring to.
The C++ Standard Library places almost all of its components (like string, cout, cin, endl, vector, map, etc.) inside the std namespace.
std::string:

This explicitly tells the compiler: "I want to use the string class that is defined within the std namespace."
It's a fully qualified name.
Why it's good practice:

Clarity: It makes it immediately obvious that string is a standard library component, not something you've defined yourself or something from another third-party library
The reason for this is that int (and other fundamental data types like char, double, bool, float, long, etc.) are built-in, fundamental types of the C++ language itself, not classes or types defined within the std namespace of the Standard Library.

int: A keyword directly recognized by the C++ compiler to represent an integer number. It's part of the core language specification.
std::string: A class (a user-defined type, albeit one provided by the standard library) that encapsulates dynamic arrays of characters. It's not a fundamental part of the language's syntax itself but is built using the language's features and placed in the std namespace.

Based on your provided main function loop, let's break down the scenarios where if (std::cin.eof()) break; would be reached and what eof means in this context.

What eof means here:
eof stands for "End Of File". In the context of std::cin (standard input), it signifies that there is no more input to be read from the input stream.

   if (std::cin.eof()) break;
Scenarios where if (std::cin.eof()) break; would be reached:
This line acts as a safety net to handle situations where the input stream is exhausted, rather than relying solely on the user typing "EXIT". Here are the primary scenarios:

Redirection from a File (and the file ends):

How it works: If you run your program and redirect its standard input from a file, for example:
eg user hits ctrl d 
*/