#ifndef  RPN_H
# define RPN_H

# include <iostream>
# include <stack>
# include <string>
# include <sstream>
# include <stdexcept>

class   RPN {
    private:
        RPN(const RPN &copy);
        RPN &operator=(const RPN &other);
        void    processOperator(const std::string &op, std::stack<int> &stack);
        bool    isOperator(const std::string &token);
        bool    isNumber(const std::string &token);
    public:
        RPN();
        ~RPN();
        void    evaluate(const std::string &expression);
};

#endif