#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>

class RPN {
private:
    std::stack<int> _stack;

    bool isOperator(const std::string& token) const;
    bool isNumber(const std::string& token) const;
    int calculate(int a, int b, char op) const;

public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    int evaluate(const std::string& expression);
};

#endif
