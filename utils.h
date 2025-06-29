#include <iostream>
#pragma once

void skipVoidPosition(std::string_view expression, std::size_t& index);

bool checkIsNegativeNumber(std::string_view expression, std::size_t index);

bool binaryOperators(char operators);

int getOperatorPriority(char expression);

int validateBrackets(std::string_view value);

int parseNumber(std::string_view expression, std::size_t& index);

void inputUser(std::string& input);
