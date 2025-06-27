#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class phoneBook 
{
private:
    Contact contacts[8];
    int contactCount;

public:
    phoneBook(); //this is the constructor 
    //It has the same name as the class itself. 
    //This is the defining characteristic of a constructor.
    void addContact();
    void searchContacts() const;
};

/*
 It has no parameters. This makes it the default constructor. If you don't provide any parameters, this is the constructor that will be called when you create an object like phoneBook myBook;.
No return type: Constructors do not have a return type (not even void). This is another defining characteristic.
*/
#endif