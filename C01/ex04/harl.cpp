#include "harl.hpp"
#include <iostream>

Harl::Harl() {}

void Harl::debug() {
    std::cout << "[ DEBUG ]\nI love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger.\n" << std::endl;
}

void Harl::info() {
    std::cout << "[ INFO ]\nI cannot believe adding extra bacon costs more money...\n" << std::endl;
}

void Harl::warning() {
    std::cout << "[ WARNING ]\nI think I deserve to have some extra bacon for free...\n" << std::endl;
}

void Harl::error() {
    std::cout << "[ ERROR ]\nThis is unacceptable! I want to speak to the manager now.\n" << std::endl;
}

void Harl::complain(std::string level) {
    typedef void (Harl::*HarlMethod)();

    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    HarlMethod methods[] = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};

    int i = 0;
    while (i < 4 && levels[i] != level)
        i++;

    switch (i) {
        case 0:
            (this->*methods[0])();
        case 1:
            (this->*methods[1])();
        case 2:
            (this->*methods[2])();
        case 3:
            (this->*methods[3])();
            break;
        default:
            std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
    }
}