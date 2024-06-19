#pragma once
#include "Tokanizer.hpp"
#include <algorithm>

class Parser {
private:
    bool isOperator(char c);
    int precedence(const Token& op);
    std::vector<Token> shoutingYard(std::vector<Token>& expression);
public:
    std::vector<Token> parseExpression(std::vector<Token>& tokenList);
};