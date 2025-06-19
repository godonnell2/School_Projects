#include "phoneBook.hpp"
#include <iostream>
#include <limits>
#include <iomanip> //for setw

phoneBook::phoneBook() : contactCount(0) {}
//constructor fn 
//phoneBook::: This is the scope resolution operator.
// It indicates that the phoneBook() function belongs to the phoneBook class.
//This colon introduces the member initializer list. 
// This is a special syntax in C++ that allows you to initialize member variables before the constructor's body ({}) is executed.
/*
This is an initializer within the member initializer list.
contactCount: This refers to the contactCount member variable of your phoneBook class.
(0): This specifies the value that contactCount will be initialized to. So, contactCount will be set to 0.
{} (Empty Braces):

This is the body of the constructor. In this specific example, the body is empty because all necessary initialization is handled by the member initializer list.
*/
void phoneBook::addContact() 
{
    if (contactCount >= 8)
        std::cout << "PhoneBook is full. Oldest contact will be overwritten." << std::endl;

    contacts[contactCount % 8].setContact();
    contactCount++;
}

void phoneBook::searchContacts() const 
{
    //part1 if count less than 8 disp that many if not 8
    int total = (contactCount < 8) ? contactCount : 8;
 // Part 2: Print the header for the short contact list
    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "Nickname" << std::endl;
 // Part 3: Loop and display short details for available contacts
    for (int i = 0; i < total; i++)
        contacts[i].displayShort(i);

  // Part 4: Prompt user for an index to view full details
    std::cout << "Enter index to view full contact: ";
    int index; //Declares an integer variable index to store the user's input.
    // Part 5: Handle user input for the index
    if (!(std::cin >> index)) 
    {
        // Part 5a: Input failure (e.g., non-numeric input, Ctrl+D)
        std::cin.clear(); // Clear error flags (failbit, eofbit)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard remaining invalid input
        std::cout << "Invalid input." << std::endl; //just lets user know
        return; // Exit the function
    }

    std::cin.ignore();
    if (index < 0 || index >= total)
        std::cout << "Index out of range." << std::endl;
    else
        contacts[index].displayFull();
}
/*
When you use std::cin >> index;, it reads only the integer value and leaves the newline character (that you press after typing the number) in the input buffer.
If you were to use std::getline immediately after this, getline would read that leftover newline and appear to skip input.
This std::cin.ignore() (with default parameters, which typically discard one character) consumes that leftover newline, preparing the input stream for any subsequent
 getline calls in other parts of your program. 

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  common way to clear the input buffer 
  cin.ignore is part of the controlling of stream
  you tupe 25 and press enter the newline is in the buffer 
  then getline is called and for the next var would store an empyt line 
  as it encounters it immediately 
  count (first argument): The maximum number of characters to extract and discard. Defaults to 1 if not specified.
delim (second argument): The "delimiter" character. If this character is encountered before count characters have been discarded, 
ignore() stops discarding characters (and discards the delimiter itself).
 Defaults to EOF (End-of-File) if not specified.
 numeric_limits is a template class that provides information about the properties of arithmetic types (like int, double, char, etc.)
  and, in this case, std::streamsize.
  std::streamsize is an integer type used to represent sizes of streams (e.g., how many characters were read/written).
.max() returns the largest possible value that an object of type std::streamsize can hold.
What it means here: By passing max(), you are telling ignore() to discard an extremely large number of characters. In practice, this means "discard all characters" up to the delimiter, because it's highly unlikely that the input buffer will contain more characters
 than the maximum value of std::streamsize.
 This is the delimiter character.
What it means here: ignore() will discard characters until it encounters a newline character (\n). Once it finds the \n, it will discard the \n itself and then stop.

*/
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