#include <iostream>
#include <stack>
#include <string>

#include "utils.h"

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
    default:
        abort();
    }
}

int calculateValues(std::stack<int>& operands, std::stack<char>& operators) {
    if (operands.size() < 2) {
        std::cout << "Need more operand";
        return -1;
    }

    int b = operands.top(); operands.pop();
    int a = operands.top(); operands.pop();
    char op = operators.top(); operators.pop();

    operands.push(calculateSubValues(a, b, op));
    return 0;
}

int calulateExpresion(const std::string&& expression) {
    std::stack<int> operands;
    std::stack<char> operators;

    for (std::size_t index{ 0 }; index < expression.length(); ++index) {

        if (std::isdigit(expression[index]) || checkIsNegativeNumber(expression, index)) {
            operands.push(parseNumber(expression, index));
        }
        else if (expression[index] == '(') {
            operators.push(expression[index]);
        }
        // В данном случае, мы высчитывает "на лету" выражение, и предложенный варинт разделения логики мне не совсем понятен
        else if (expression[index] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                if (calculateValues(operands, operators) != 0) {
                    return -1;
                }
            }

            if (!operands.empty() && !operators.empty() && operators.top() == '(') {
                operators.pop();
            }
        }
        if (binaryOperators(expression[index])) {
            while (!operators.empty() &&
                getOperatorPriority(operators.top()) >= getOperatorPriority(expression[index]))
            {
                if (calculateValues(operands, operators))
                    return -1;
            }
            operators.push(expression[index]);
        }

    }

    while (!operators.empty()) {
        if (calculateValues(operands, operators))
            return -1;
    }
    if (operands.size() > 1) {
        std::cout << ("Invalid expression");
        return -1;
    }

    return operands.top();
}