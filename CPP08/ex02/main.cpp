#include "MutantStack.hpp"

int main()
{
    MutantStack<int> mstack;

    mstack.push(1);
    mstack.push(17);

    std::cout << "Top element: " << mstack.top() << std::endl;
    mstack.pop();
    std::cout << "Stack size after pop: " << mstack.size() << std::endl;

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    std::cout << "\nIterating with normal iterator:" << std::endl;
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    while (it != ite)
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;

    std::cout << "\nIterating with const_iterator:" << std::endl;
    MutantStack<int>::const_iterator cit = mstack.begin();
    MutantStack<int>::const_iterator cite = mstack.end();

    while (cit != cite)
    {
        std::cout << *cit << " ";
        ++cit;
    }
    std::cout << std::endl;

    std::cout << "\nIterating with reverse_iterator:" << std::endl;
    MutantStack<int>::reverse_iterator rit = mstack.rbegin();
    MutantStack<int>::reverse_iterator rite = mstack.rend();

    while (rit != rite)
    {
        std::cout << *rit << " ";
        ++rit;
    }
    std::cout << std::endl;

    std::cout << "\nIterating with const_reverse_iterator:" << std::endl;
    MutantStack<int>::const_reverse_iterator crit = mstack.rbegin();
    MutantStack<int>::const_reverse_iterator crite = mstack.rend();

    while (crit != crite)
    {
        std::cout << *crit << " ";
        ++crit;
    }
    std::cout << std::endl;
    
    std::stack<int> s(mstack);
    std::cout << "\nOriginal stack size: " << mstack.size() << std::endl;
    std::cout << "Copied stack size: " << s.size() << std::endl;

    std::cout << "\nChecking copied stack elements:" << std::endl;
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;

    return 0;
}