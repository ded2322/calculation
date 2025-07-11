#include <iostream>
#include <stack>

int calculateSubValues(int a, int b, char op) {
    switch (op) {
        case '+': 
            return a + b;
        case '-': 
            return a - b;
        case '*': 
            return a * b;
        case '/': 
            return a / b;
        case '(': 
            return 0;
        default:
            throw std::runtime_error("Unknown operand");
    }
}

int calculateValues(std::stack<int>& operands, std::stack<char>& operators) {
    if (operands.size() < 2) {
        std::cout << "Need more operand";
        return -1;
    }

    int b = operands.top(); operands.pop();
    int a = operands.top(); operands.pop();
    char op  = operators.top(); operators.pop();

    operands.push(calculateSubValues(a, b, op));
    return 0;
}
