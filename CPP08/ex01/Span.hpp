#ifndef SPAN_H
# define SPAN_H

# include <iostream>
# include <vector>
# include <algorithm>
# include <stdexcept>
# include <climits>
# include <random>

class Span {

    private:
        unsigned int _maxSize;
        std::vector<int> _numbers;

    public:
        Span();
        Span(unsigned int N);
        ~Span();
        Span(const Span &copy);
        Span& operator=(const Span &other);

        void    addNumber(int num);
        int     shortestSpan();
        int     longestSpan();
        void    fillSpan();
};

#endif