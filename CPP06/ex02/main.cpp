#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <exception>

Base* generate(void) {
    srand(static_cast<unsigned>(time(0)));
    int randomNumb = rand() % 3;

    if (randomNumb == 0)
        return new A;
    else if (randomNumb == 1)
        return new B;
    else
        return new C;
}

void identify(Base* p) {
    if (dynamic_cast<A*>(p)) {
        std::cout << "A" << std::endl;
    } else if (dynamic_cast<B*>(p)) {
        std::cout << "B" << std::endl;
    } else if (dynamic_cast<C*>(p)) {
        std::cout << "C" << std::endl;
    }
}

void identify(Base& p) {
    try {
        dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
    }
    catch (const std::bad_cast& e) {}
    try {
        dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
    }
    catch (const std::bad_cast& e) {}
    try {
        dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
    } catch (const std::bad_cast& e) {}
}

int main() {
    Base *ptr = generate();
    
    std::cout << "Identifying by pointer: ";
    identify(ptr);
    
    std::cout << "Identifying by reference: ";
    identify(*ptr);
    
    delete ptr;
    return 0;
}