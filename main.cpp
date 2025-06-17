#include <iostream>
#include <vector>
#include <cctype>
#include <stack>

int operatorPriority(char& expression) {
    switch (expression) {
    case '+':
    case '-':
        return 1;
    case '*': return 2;
    case '/': return 2;
    case '(': return 0;
    default :
        return -1;
    }
}

void skipVoidPosition(std::string_view expression, std::size_t& index){
    if(index < expression.length() && std::isspace(expression[index]))
        ++index;
}

int parseNumber(std::string_view expression, std::size_t& index) {
    skipVoidPosition(expression, index);

    bool is_negative = false;
    if (expression[index] == '-' || expression[index] == '+') {
        if (index + 1  < expression.length() && std::isdigit(expression[index + 1])) {
            is_negative = true;
        }
        ++index;
    }

    int result {0}; 
    std::vector<int> operand; 
    std::vector<char> operators;

    while(index < expression.length() && std::isdigit(expression[index])) {
        result = result * 10 + static_cast<int>(expression[index]) - static_cast<int>('0');
        ++index;
    }

    return is_negative ? -result : result;
}

void checkBrackets(std::string_view value) {
    std::vector<char> stack;

    for(char a : value){
        if (a == '(') 
            stack.push_back(a);
        else if(a == ')') {
            if (stack.empty()) {
                throw std::runtime_error("Uncorrect brackets, not found open brackets");
            }
            stack.pop_back();
        }
    }
    if(!stack.empty()) {
        throw std::runtime_error("Uncorrect brackets");
    }
}

int calculateResult(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '(': return 0;
        default:
            throw std::runtime_error("Unknown operand");
    }
}

void processOperator(std::stack<int>& operands, std::stack<char>& operators) {
    if (operands.size() < 2) throw std::runtime_error("Need more operand");

    int b = operands.top(); operands.pop();
    int a = operands.top(); operands.pop();
    char op  = operators.top(); operators.pop();

    operands.push(calculateResult(a, b, op));
}

int main() {
    std::cout << "For exit calc input: -1\n";
    while (true) {
        std::string input;
        std::cout << "Input data: ";
        std::getline(std::cin, input);
        if (input == "-1") break;

        checkBrackets(input);
        std::size_t index { 0 };
        
        std::stack<int> operands;
        std::stack<char> operators; 

        while(index < input.length()) {
            skipVoidPosition(input, index);

            if ( std::isdigit(input[index]) || input[index] == '-') {
                int number = parseNumber(input, index);
                operands.push(number);
            } else if (input[index] == '(') {
                operators.push(input[index]);
                ++index;
            } else if (input[index] == ')') {
                if (!operators.empty() && operators.top() != '(') {
                    processOperator(operands, operators);
                }
                if (!operators.empty() && operators.top() == '(') {
                    operators.pop();
                }
                if (operators.empty()) 
                    throw std::runtime_error("Invalide brackets");
                ++index;
            } else if (input[index] == '+' || input[index] == '-' || input[index] == '*' || input[index] == '/') {

                while ( !operators.empty() &&
                    operatorPriority(operators.top()) >= operatorPriority(input[index])) {
                        processOperator(operands, operators);
                }

                operators.push(input[index]);
                ++index;
            }
        }
        
        while (!operators.empty()) {
            processOperator(operands, operators);
        }
        if(operands.size() > 1) {
            throw std::runtime_error("Invalid expression");
        }
        std::cout << operands.top() << '\n';
    }
}
