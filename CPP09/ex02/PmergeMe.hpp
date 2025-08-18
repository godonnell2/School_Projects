#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>
#include <stdexcept>
#include <iomanip>

class PmergeMe {
    private:
        std::deque<int> _deque;
        std::list<int> _list;

        bool isValidNumber(const std::string& str);

        // Deque sorting helpers
        std::deque<int> fordJohnsonSortDeque(const std::deque<int>& input);
        std::deque<int> generateJacobsthal(int max);
        void insertWithJacobsthal(std::deque<int>& sorted, std::deque<int>& toInsert);

        // List sorting helpers
        std::list<int> fordJohnsonSortList(const std::list<int>& input);
        void insertWithJacobsthal(std::list<int>& sorted, std::list<int>& toInsert);
    public:
        PmergeMe(char **av);
        ~PmergeMe();

        void display();
};

#endif
