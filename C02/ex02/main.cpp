#include "Fixed.hpp"

int main() {
    Fixed a(10.5f);
    Fixed b(2);

    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a / b = " << a / b << std::endl;

    std::cout << "a > b? " << (a > b) << std::endl;
    std::cout << "a == b? " << (a == b) << std::endl;

    Fixed x(5.5f); 
    std::cout << "Initial x = " << x << std::endl;
    std::cout << "++x: "<< ++x << std::endl;  //adds 1 raw unit = 1/256 ≈ 0.00391)
    x++ ;
    std::cout << "x after x++: " << x << std::endl;
    std::cout << "--x: " << --x << std::endl; 
    x-- ;
    std::cout << "x after x--: " << x << std::endl;
     
    Fixed f1(7.7f);
    Fixed f2(3.3f);
    std::cout << "min(f1, f2) = " << Fixed::min(f1, f2) << std::endl; 
    std::cout << "max(f1, f2) = " << Fixed::max(f1, f2) << std::endl;

}