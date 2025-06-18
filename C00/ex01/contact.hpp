#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact 
{
private:
    std::string firstName;
    std::string lastName;
    std::string nickname;
    std::string phoneNumber;
    std::string darkestSecret;

public:
    void setContact();
    void displayShort(int index) const;
    void displayFull() const;
};

#endif

/*
private
This is where data is hidden from the outside world. 
Only methods inside the class can access them directly.
 std::string firstName; fields that store info
 They are private so that users of the class can’t directly access 
 or change them, 
 which is good object-oriented design.
 public
 These are functions (methods) 
 that you can call from outside to interact with the Contact.
*/