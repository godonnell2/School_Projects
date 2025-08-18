#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char **av) {
    for (int i = 1; av[i]; ++i) {
        std::string str = av[i];
        if (!isValidNumber(str))
            throw std::runtime_error("Error");

        int value = std::atoi(str.c_str());
        if (value < 0)
            throw std::runtime_error("Error");

        if (std::find(_deque.begin(), _deque.end(), value) == _deque.end())
            _deque.push_back(value);
        if (std::find(_list.begin(), _list.end(), value) == _list.end())
            _list.push_back(value);
    }
}

PmergeMe::~PmergeMe() {}

bool PmergeMe::isValidNumber(const std::string& str) {
    for (size_t i = 0; i < str.size(); ++i)
        if (!std::isdigit(str[i]))
            return false;
    return true;
}

// -------------------- Display Function --------------------

void PmergeMe::display() {
    std::cout << "Before: ";
    for (size_t i = 0; i < _deque.size(); ++i)
        std::cout << _deque[i] << " ";
    std::cout << std::endl;

    struct timeval start, end;

    // --- Deque Sorting ---
    gettimeofday(&start, NULL);
    std::deque<int> sortedDeque = fordJohnsonSortDeque(_deque);
    gettimeofday(&end, NULL);
    long timeDeque = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    std::cout << "After: ";
    for (size_t i = 0; i < sortedDeque.size(); ++i)
        std::cout << sortedDeque[i] << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << _deque.size()
          << " elements with std::deque : " << std::fixed << std::setprecision(5)
          << (timeDeque / 1000000.0) << " us" << std::endl;

    // --- List Sorting ---
    gettimeofday(&start, NULL);
    std::list<int> sortedList = fordJohnsonSortList(_list);
    gettimeofday(&end, NULL);
    long timeList = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    std::cout << "Time to process a range of " << _list.size()
          << " elements with std::list  : " << std::fixed << std::setprecision(5)
          << (timeList / 1000000.0) << " us" << std::endl;
}

// -------------------- Deque Sort --------------------

std::deque<int> PmergeMe::fordJohnsonSortDeque(const std::deque<int>& input) {
    if (input.size() <= 1)
        return input;

    std::deque<int> small, big;
    for (size_t i = 0; i + 1 < input.size(); i += 2) {
        if (input[i] < input[i + 1]) {
            small.push_back(input[i]);
            big.push_back(input[i + 1]);
        } else {
            small.push_back(input[i + 1]);
            big.push_back(input[i]);
        }
    }
    if (input.size() % 2 != 0)
        small.push_back(input.back());

    std::deque<int> sorted = fordJohnsonSortDeque(big);
    std::deque<int> result;
    result.push_back(sorted[0]);
    if (!small.empty())
        result.insert(std::lower_bound(result.begin(), result.end(), small[0]), small[0]);

    for (size_t i = 1; i < sorted.size(); ++i)
        result.insert(std::lower_bound(result.begin(), result.end(), sorted[i]), sorted[i]);

    insertWithJacobsthal(result, small);

    return result;
}

std::deque<int> PmergeMe::generateJacobsthal(int max) {
    std::deque<int> seq;
    seq.push_back(0);
    seq.push_back(1);

    while (true) {
        int next = seq[seq.size() - 1] + 2 * seq[seq.size() - 2];
        if (next > max) break;
        seq.push_back(next);
    }
    return seq;
}

void PmergeMe::insertWithJacobsthal(std::deque<int>& sorted, std::deque<int>& toInsert) {
    if (toInsert.size() <= 1)
        return;

    std::deque<int> jacob = generateJacobsthal(toInsert.size() - 1);
    std::vector<bool> inserted(toInsert.size(), false);
    inserted[0] = true;

    for (size_t i = 1; i < jacob.size(); ++i) {
        int idx = jacob[i];
        if (idx < (int)toInsert.size() && !inserted[idx]) {
            sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), toInsert[idx]), toInsert[idx]);
            inserted[idx] = true;
        }
    }

    for (size_t i = 0; i < toInsert.size(); ++i) {
        if (!inserted[i])
            sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), toInsert[i]), toInsert[i]);
    }
}

// -------------------- List Sort --------------------

std::list<int> PmergeMe::fordJohnsonSortList(const std::list<int>& input) {
    if (input.size() <= 1)
        return input;

    std::list<int> small, big;
    std::list<int>::const_iterator it = input.begin();

    while (it != input.end()) {
        int first = *it++;
        if (it != input.end()) {
            int second = *it++;
            if (first < second) {
                small.push_back(first);
                big.push_back(second);
            } else {
                small.push_back(second);
                big.push_back(first);
            }
        } else {
            small.push_back(first);
        }
    }

    std::list<int> sorted = fordJohnsonSortList(big);
    std::list<int> result;
    result.push_back(sorted.front());

    std::list<int>::iterator sm_it = small.begin();
    if (sm_it != small.end()) {
        result.insert(std::lower_bound(result.begin(), result.end(), *sm_it), *sm_it);
        ++sm_it;
    }

    for (std::list<int>::iterator it = ++sorted.begin(); it != sorted.end(); ++it)
        result.insert(std::lower_bound(result.begin(), result.end(), *it), *it);

    insertWithJacobsthal(result, small);

    return result;
}

void PmergeMe::insertWithJacobsthal(std::list<int>& sorted, std::list<int>& toInsert) {
    if (toInsert.size() <= 1)
        return;

    std::deque<int> jacob = generateJacobsthal(toInsert.size() - 1);
    std::vector<int> buffer(toInsert.begin(), toInsert.end());
    std::vector<bool> inserted(buffer.size(), false);
    inserted[0] = true;

    for (size_t i = 1; i < jacob.size(); ++i) {
        int idx = jacob[i];
        if (idx < (int)buffer.size() && !inserted[idx]) {
            sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), buffer[idx]), buffer[idx]);
            inserted[idx] = true;
        }
    }

    for (size_t i = 0; i < buffer.size(); ++i) {
        if (!inserted[i])
            sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), buffer[i]), buffer[i]);
    }
}
