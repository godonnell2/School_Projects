#include "phoneBook.hpp"
#include <iostream>
#include <limits>

PhoneBook::PhoneBook() : contactCount(0) {}

void PhoneBook::addContact() {
    if (contactCount >= 8)
        std::cout << "PhoneBook is full. Oldest contact will be overwritten." << std::endl;

    contacts[contactCount % 8].setContact();
    contactCount++;
}

void PhoneBook::searchContacts() const {
    int total = (contactCount < 8) ? contactCount : 8;

    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "Nickname" << std::endl;

    for (int i = 0; i < total; i++)
        contacts[i].displayShort(i);

    std::cout << "Enter index to view full contact: ";
    int index;
    if (!(std::cin >> index)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input." << std::endl;
        return;
    }

    std::cin.ignore();
    if (index < 0 || index >= total)
        std::cout << "Index out of range." << std::endl;
    else
        contacts[index].displayFull();
}

int main() {
    PhoneBook book;
    std::string command;

    std::cout << "Welcome to the Awesome PhoneBook. Commands: ADD, SEARCH, EXIT" << std::endl;

    while (true) {
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