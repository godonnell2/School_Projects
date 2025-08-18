#include "Span.hpp"

Span::Span() : _maxSize(2) {
}

Span::~Span() {
}

Span::Span(unsigned int N) : _maxSize(N) {
}

Span::Span(const Span &copy) : _maxSize(copy._maxSize), _numbers(copy._numbers) {
}

Span& Span::operator=(const Span &other) {
    if (this != &other) {
        _numbers = other._numbers;
    }
    return (*this);
}

void    Span::addNumber(int num) {
    if (_numbers.size() >= _maxSize)
        throw std::overflow_error("Span is already full");
    _numbers.push_back(num);
}

int     Span::shortestSpan() {
    if (_numbers.size() < 2)
        throw std::logic_error("Not enough numbers");
    
    std::vector<int> sortedNumbers = _numbers;
    std::sort(sortedNumbers.begin(), sortedNumbers.end());

    int min = INT_MAX;
    for (size_t i = 1; i < sortedNumbers.size(); i++) {
        int diff = sortedNumbers[i] - sortedNumbers[i - 1];
        if (diff < min)
            min = diff;
    }
    return (min);
}

int     Span::longestSpan() {
    if (_numbers.size() < 2)
        throw std::logic_error("Not enough numbers");
    
    int min = *std::min_element(_numbers.begin(), _numbers.end());
    int max = *std::max_element(_numbers.begin(), _numbers.end());

    return (max - min);
}

void    Span::fillSpan() {
    if (_numbers.size() >= _maxSize)
        throw std::overflow_error("Span is already full");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, INT_MAX);

    while (_numbers.size() < _maxSize) {
        addNumber(dist(gen));
    }
}