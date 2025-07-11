#include <iostream>
#include <vector>
#include <cctype>
#include <stack>
#include <string_view>

#include "utils.h"
#include "calculate.h"
#include "tcp_server.h"

int calulateExpresion(const std::string& expression) {
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
    std::string start_text { "For exit calculate input: -1\n" };
    
    TcpServer server(8080);
    if(!server.startTcpServer()) return -1;
    
    if(server.acceptClient()) {
        server.sendMessage(start_text);

        while(true) {
            std::string entered_expression {"Entered expression: "};
            server.sendMessage(entered_expression);

            std::string user_message { server.readMessage() };
            if(user_message == "-1") {
                server.closeUserConnection();
                break;
            }

            std::cout << "User input: " << user_message << "\n";
                
            if (validateBrackets(user_message) > -1) {
                std::string result { "Your result: " + std::to_string(calulateExpresion(user_message)) + "\n"};
                std::cout << result << "\n";
                server.sendMessage(result);
            }

        }

        server.closeTcpServer();
    }

    // while (true) {
    //     std::string input;
    //     inputUser(input);

    //     if (input == "-1") break;

    //     // Before start calculate expression, check brackets
    //     if (validateBrackets(input) > -1) {
    //         std::cout << calulateExpresion(input) << '\n';
    //         // std::cout << calulateExpresion("((10+2)*2)") << '\n';
    //     }
    // }
}
