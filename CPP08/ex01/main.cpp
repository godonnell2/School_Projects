#include "Span.hpp"

int main() {
    try {

        std::cout << "==== TEST 1: Small Span ====" << std::endl;
        Span sp = Span(5);

        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;

        std::cout << "==== TEST 2: Large Span (10,000 numbers) ====" << std::endl;
        Span bigSpan(10000);
        bigSpan.fillSpan();

        std::cout << "Shortest Span: " << bigSpan.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << bigSpan.longestSpan() << std::endl;
    }
    catch (const std::exception &e) {
    std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}