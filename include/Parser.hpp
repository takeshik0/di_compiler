#pragma once
#include "Tokanizer.hpp"
#include <stack>
#include <algorithm>

class Parser {
private:

    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/');
    }

    int precedence(const Token& op) {
        switch (op.value.front()) {
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            default:
                return 0;
        }
    }

    std::vector<Token> shoutingYard(std::vector<Token>& expression) {
    std::stack<Token> operators;
    std::vector<Token> output;

    for (const auto element : expression) {
        if(std::isdigit(element.value.front())) {
            output.push_back(element);
        } else if (isOperator(element.value.front())) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(element)) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(element);
        } else if (element.value.front() == '(') {
            operators.push(element);
        } else if (element.value.front() == ')') {
            while(!operators.empty() && operators.top().value.front() != '(') {
                output.push_back(operators.top());
                operators.pop();
            }
            if(!operators.empty()) {
                operators.pop();
            }
        }
    }

    // Pop all the operators left in the stack
    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }

        return output;
    }   
public:
    std::vector<Token> parseExpression(std::vector<Token>& tokenList) {
        std::vector<Token> expression;
        auto start = std::find(tokenList.begin(), tokenList.end(), Token {.type = TokenType::PrentacisIsOpen, .value = "("});
        auto end = std::find(tokenList.rbegin(), tokenList.rend(), Token {.type = TokenType::PrentacisIsClose, .value = ")"});
        std::copy(start + 1, end.base() - 1, std::back_inserter(expression));
        tokenList.erase(start + 1, end.base() - 1);
        expression = shoutingYard(expression);
        tokenList.insert(start + 1, expression.begin(), expression.end());
        return tokenList;
    }   
};