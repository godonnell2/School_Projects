#ifndef MUTANTSTACK_H
# define MUTANTSTACK_H

# include <iostream>
# include <vector>
# include <list>
# include <deque>
# include <stack>

template <typename T>
class MutantStack : public std::stack<T> {

    public:
        typedef typename std::deque<T>::iterator iterator;
        typedef typename std::deque<T>::const_iterator const_iterator;
        typedef typename std::deque<T>::reverse_iterator reverse_iterator;
        typedef typename std::deque<T>::const_reverse_iterator const_reverse_iterator;

        MutantStack() : std::stack<T>() {}
        ~MutantStack() {}
        MutantStack(const MutantStack &copy) : std::stack<T>(copy) {}
        MutantStack &operator=(const MutantStack &other) {
            if (this != &other) {
                std::stack<T>::operator=(other);
            }
            return (*this);
        }

        iterator begin() {
            return this->c.begin();
        }

        iterator end() {
            return this->c.end();
        }

        const_iterator begin() const {
            return this->c.begin();
        }

        const_iterator end() const {
            return this->c.end();
        }

        reverse_iterator rbegin() {
            return this->c.rbegin();
        }
    
        reverse_iterator rend() {
            return this->c.rend();
        }
    
        const_reverse_iterator rbegin() const {
            return this->c.rbegin();
        }
    
        const_reverse_iterator rend() const {
            return this->c.rend();
        }
};

#endif