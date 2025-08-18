#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

void    RPN::evaluate(const std::string &expression)
{
    std::stack<int> stack;
    std::istringstream ss(expression);
    std::string token;

    while (ss >> token)
    {
        if (isNumber(token))
            stack.push(std::stoi(token));
        else if (isOperator(token))
        {
            if (stack.size() < 2)
            {
                std::cerr << "Error: not enough numbers" << std::endl;
                return;
            }
            processOperator(token, stack);
        }
        else
        {
            std::cerr << "Error" << std::endl;
            return;
        }
    }
    if (stack.size() != 1)
    {
        std::cerr << "Error: the stack has more than one value left" << std::endl;
        return;
    }
    std::cout << stack.top() << std::endl;
}

void    RPN::processOperator(const std::string &op, std::stack<int> &stack)
{
    int b = stack.top();
    stack.pop();
    int a = stack.top();
    stack.pop();
    int result = 0;

    if (op == "+")
        result = a + b;
    else if (op == "-")
        result = a - b;
    else if (op == "*")
        result = a * b;
    else if (op == "/")
    {
        if (b == 0)
        {
            std::cerr << "Error: division by zero" << std::endl;
            return;
        }
        result = a / b;
    }
    else
    {
        std::cerr << "Error" << std::endl;
        return;
    }

    stack.push(result);
}

bool    RPN::isOperator(const std::string &token)
{
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

bool    RPN::isNumber(const std::string &token)
{
    for (char c : token)
    {
        if (!std::isdigit(c))
            return false;
    }
    return true;
}
