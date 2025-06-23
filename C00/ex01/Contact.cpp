#include "Contact.hpp"
#include <iostream>
#include <iomanip>

bool isDigits(const std::string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i]))
            return false;
    }
    return !str.empty(); // Ensure it's not empty
}

void Contact::setContact() {
    std::cout << "First Name: ";
    std::getline(std::cin, firstName);
    std::cout << "Last Name: ";
    std::getline(std::cin, lastName);
    std::cout << "Nickname: ";
    std::getline(std::cin, nickname);
    while (true) 
    {
        std::cout << "Phone Number: ";
        std::getline(std::cin, phoneNumber);

        if (isDigits(phoneNumber)) 
        {
            break;
        } 
        else 
        {
            std::cout << "Invalid phone number. Please enter only digits.\n";
        }
    }
    std::cout << "Darkest Secret: ";
    std::getline(std::cin, darkestSecret);
}


void Contact::displayShort(int index) const 
{
     // Create temporary strings for display purposes,
    // working with the actual member variables.
    std::string dispFirstName = firstName;
    if (dispFirstName.length() > 10) 
        dispFirstName = dispFirstName.substr(0, 9) + ".";

    std::string dispLastName = lastName;
    if (dispLastName.length() > 10) 
        dispLastName = dispLastName.substr(0, 9) + ".";

    std::string dispNickname = nickname;
    if (dispNickname.length() > 10) 
        dispNickname = dispNickname.substr(0, 9) + ".";

    
    std::cout << std::setw(10) << index << "|"
              << std::setw(10) << dispFirstName << "|"
              << std::setw(10) << dispLastName << "|"
              << std::setw(10) << dispNickname << std::endl;
}

void Contact::displayFull() const 
{
    std::cout << "First Name: " << firstName << std::endl;
    std::cout << "Last Name: " << lastName << std::endl;
    std::cout << "Nickname: " << nickname << std::endl;
    std::cout << "Phone Number: " << phoneNumber << std::endl;
    std::cout << "Darkest Secret: " << darkestSecret << std::endl;
}

/*

Hey, if the string you give me is longer than 10 characters, 
I’ll return the first 9 characters plus a dot (.). 
If it’s shorter or exactly 10, I’ll just return it untouched.”
setw(10) set width
"The next thing you print should take up at least 10 characters of space."

If the content is shorter than 10 characters,
 it adds spaces to the left (by default) to make it fit.

Set Contact
std::cin user input from the keyboard. like scanf
But it stops at the first whitespace (space, tab, newline).
would stop at first name if you didnt use getline 
read entire line from input including spaces 
until user hit enter
std::cin	Whitespace	❌ No	Quick one-word input
std::getline	Newline	✅ Yes	Full-line input (e.g., names)
std::getline(from_here, put_it_here);
It keeps reading until it encounters a newline character (\n), 
which is inserted when the user presses Enter.
It stops reading.

It discards the newline (doesn’t include it in firstName).

It stores everything before that newline into your variable.
modern way 
A lambda in C++ is basically an inline anonymous function — a short, 
one-off function you can define and use right where you need it.
a lambda fn named truncate 
void Contact::displayShort(int index) const 
{
    auto truncate = [](const std::string& str) 
    {
        return (str.length() > 10) ? str.substr(0, 9) + "." : str;
    };
    std::cout << std::setw(10) << index << "|"
              << std::setw(10) << truncate(firstName) << "|"
              << std::setw(10) << truncate(lastName) << "|"
              << std::setw(10) << truncate(nickname) << std::endl;
}
*/