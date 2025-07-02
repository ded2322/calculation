#include <iostream>
#include <vector>
#include <cctype>
#include <stack>
#include <string_view>

#include "calculate.h"
#include "utils.h"

int main() {
    std::cout << "For exit calc input: -1\n";
    while (true) {
        std::string input;
        inputUser(input);

        if (input == "-1") break;

        // Before start calculate expression, check brackets
        if (validateBrackets(input) > -1) {
            std::cout << calulateExpresion(input) << '\n';
        }
    }
}
