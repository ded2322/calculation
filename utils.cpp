#include <stack>
#include <iostream>
#include <string>
#include <charconv>

void skipVoidPosition(std::string_view expression, std::size_t& index) {
    while (index < expression.length() && std::isspace(expression[index])) {
        ++index;
    }
}

bool checkIsNegativeNumber(std::string_view expression, std::size_t index) {
    return (index + 1 < expression.length() && expression[index] == '-' && std::isdigit(expression[index + 1]));
}

bool binaryOperators(char operators) {
    return operators == '+' || operators == '-' || operators == '*' || operators == '/';
}

int getOperator(const char& expression) {
    switch (expression) {
    case '+':
        return '+';
    case '-':
        return '-';
    case '*':
        return '*';
    case '/':
        return '/';
    default:
        abort();
    }
}

int validateBrackets(std::string_view value) {
    std::stack<char> stack;

    for (char a : value) {
        if (a == '(')
            stack.push(a);
        else if (a == ')') {
            if (stack.empty()) {
                std::cout << "Uncorrect brackets, not found open brackets";
                return -1;
            }
            stack.pop();
        }
    }
    if (!stack.empty()) {
        std::cout << ("Uncorrect brackets") << '\n';
        return -1;
    }
    return 0;
}


int parseNumber(std::string_view expression, std::size_t& global_index) {
    std::size_t local_index{ global_index };

    bool is_negative = checkIsNegativeNumber(expression, global_index);
    if (is_negative)
        ++local_index;

    int result{ 0 };
    while (local_index < expression.length()) {
        global_index = local_index;
        result = result * 10 + static_cast<int>(expression[local_index]) - static_cast<int>('0');
        ++local_index;
    }

    return is_negative ? -result : result;
}

std::string inputUser() {
    std::cout << "Input data: ";
    std::string input;
    std::getline(std::cin, input);
    return input;
}
