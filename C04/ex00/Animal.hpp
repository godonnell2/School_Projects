#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal {
protected:
    std::string type;

public:
    Animal();
    Animal(const Animal& other);
    Animal& operator=(const Animal& other);
    virtual ~Animal(); //new is the virutal destructor

    virtual void makeSound() const; //and the virt method
    std::string getType() const;
};

#endif
//→ the class itself and all derived classes can access it.