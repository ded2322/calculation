#include <iostream>
#include <vector>
#include <cctype>
#include <stack>
#include <string_view>

#include "utils.h"
#include "calculate.h"

int calulateExpresion(std::string_view expression) {
    std::stack<int> operands;
    std::stack<char> operators;

    for (std::size_t index{ 0 }; index < expression.length(); ++index) {

        if (std::isdigit(expression[index]) || checkIsNegativeNumber(expression, index)) {
            operands.push(parseNumber(expression, index));
        }
        if (expression[index] == '(') {
            operators.push(expression[index]);
        }
        if (expression[index] == ')') {
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

int main() {
    std::cout << "For exit calc input: -1\n";
    while (true) {
        std::string input;
        inputUser(input);

        if (input == "-1") break;

        // Before start calculate expression, check brackets
        if (validateBrackets(input) > -1) {
            std::cout << calulateExpresion(input) << '\n';
            // std::cout << calulateExpresion("((10+2)*2)") << '\n';
        }
    }
}
