#include "Tokanizer.hpp"

std::vector<Token> Tokanizer::tokanize(std::string& inputFilrString) {
    std::vector<Token> tokenList;

    bool IsPrentacisOpen = false;
    int counterForKeywords = 0;
    for(int pos = 0; pos < inputFilrString.size(); pos++) {
        if(std::isspace(inputFilrString[pos]) || inputFilrString[pos] == '\n') { continue; }
        if(inputFilrString[pos] == StringTokens.at(TokenType::KwPrint)[counterForKeywords]) {
            counterForKeywords++;
        }
        if(counterForKeywords == StringTokens.at(TokenType::KwPrint).size()) {
            tokenList.push_back({TokenType::KwPrint, StringTokens.at(TokenType::KwPrint)});
            counterForKeywords = 0; 
        }
        if(inputFilrString[pos] == '(') {
            tokenList.push_back({TokenType::PrentacisIsOpen, StringTokens.at(TokenType::PrentacisIsOpen)});
            IsPrentacisOpen = true;
        }
        if(std::isdigit(inputFilrString[pos])) {
            std::string num;
            while(std::isdigit(inputFilrString[pos])) {
                num.push_back(inputFilrString[pos]);
                pos++;
            }
            tokenList.push_back({TokenType::KwInt, num});
        }
        if(inputFilrString[pos] == '+') {
            tokenList.push_back({TokenType::OpAdd, StringTokens.at(TokenType::OpAdd)});
        }
        if(inputFilrString[pos] == '-') {
            tokenList.push_back({TokenType::OpSubtruct, StringTokens.at(TokenType::OpSubtruct)});
        }
        if(inputFilrString[pos] == ')') {
            if(IsPrentacisOpen) {
                tokenList.push_back({TokenType::PrentacisIsClose, StringTokens.at(TokenType::PrentacisIsClose)});
                IsPrentacisOpen = false;
            } else {
                tokenList.push_back({TokenType::PrentacisIsClose, StringTokens.at(TokenType::PrentacisIsClose)});
                IsPrentacisOpen = false;
                //throw std::invalid_argument("prentacis not open\n");
            }
        }
        if(inputFilrString[pos] == ';') {
            tokenList.push_back({TokenType::IsSemicolon, StringTokens.at(TokenType::IsSemicolon)});
        } else if(inputFilrString[pos] == *inputFilrString.end()) {
            throw std::invalid_argument("semicolon expected\n");
        }
    }
    return tokenList;
}