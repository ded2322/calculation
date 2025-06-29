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
    
    for(std::size_t index { 0 }; index < expression.length(); ++index) {

        if ( std::isdigit(expression[index]) || checkIsNegativeNumber(expression, index) ) {
            int number = parseNumber(expression, index);
            operands.push(number);
        } else if (expression[index] == '(') {
            operators.push(expression[index]);
            ++index;
        } else if (expression[index] == ')') {
            if (!operators.empty() && operators.top() != '(') {
                calculateValues(operands, operators);
            }
            if (!operators.empty() && operators.top() == '(') {
                operators.pop();
            }
            if (operators.empty()){ 
                std::cout << "Invalide brackets";
                return -1;
            }
            ++index;
        } else if ( binaryOperators(expression[index]) ) {
            while ( !operators.empty() &&
                getOperatorPriority(operators.top()) >= getOperatorPriority(expression[index])) 
                {
                    if (calculateValues(operands, operators))
                        return -1;
                }
            operators.push(expression[index]);
            ++index;
        }

    }

    while (!operators.empty()) {
        if (calculateValues(operands, operators))
            return -1;
    }
    if(operands.size() > 1) {
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
        if(validateBrackets(input) > -1) {
            std::cout << calulateExpresion(input) << '\n';
        }
    }
}
