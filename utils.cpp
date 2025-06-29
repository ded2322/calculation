#include <stack>
#include <iostream>
#include <string>
#include <charconv>

void skipVoidPosition(std::string_view expression, std::size_t& index){
    if(index < expression.length() && std::isspace(expression[index]))
        ++index;
}

bool checkIsNegativeNumber(std::string_view expression, std::size_t index) {
    return (index + 1  < expression.length() && std::isdigit(expression[index + 1]));
}

bool binaryOperators(char operators) {
    return operators == '+' || operators == '-' || operators == '*' || operators == '/';
}

int getOperatorPriority(char expression) {
    switch (expression) {
    case '+':
    case '-':
        return 1;
    case '*': 
        return 2;
    case '/': 
        return 2;
    default :
        return -1;
    }
}

int validateBrackets(std::string_view value) {
    std::stack<char> stack;

    for(char a : value){
        if (a == '(') 
            stack.push(a);
        else if(a == ')') {
            if (stack.empty()) {
                std::cout << "Uncorrect brackets, not found open brackets";
                return -1;
            }
            stack.pop();
        }
    }
    if(!stack.empty()) {
        std::cout << ("Uncorrect brackets");
        return -1;
    }
    return 0;
}


int parseNumber(std::string_view expression, std::size_t& index) { 
    // skipVoidPosition(expression, index);

    bool is_negative = checkIsNegativeNumber(expression, index);
    // Skip position
    if (is_negative)
        ++index;
    
    int result {0}; 
    while(index < expression.length() && std::isdigit(expression[index])) {
        result = result * 10 + static_cast<int>(expression[index]) - static_cast<int>('0');
        ++index;
    }

    return is_negative ? -result : result;
}

void inputUser(std::string& input) {
    std::cout << "Input data: ";
    std::getline(std::cin, input);
}
