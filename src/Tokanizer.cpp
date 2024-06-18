#include "Tokanizer.hpp"
#include <stdexcept>

std::vector<Token> Tokanizer::tokanize(std::string& inputFilrString) {

    std::vector<Token> tokenList;
    for(int pos = 0; pos < inputFilrString.size(); pos++) {
        if (std::isspace(inputFilrString[pos]) || inputFilrString[pos] == '\n') { continue; }
        
        const auto PRINT_WORD = StringTokens.at(TokenType::KwPrint);
        if (inputFilrString.compare(pos, PRINT_WORD.size(), PRINT_WORD) == 0) {
            tokenList.push_back({TokenType::KwPrint, PRINT_WORD});
            pos += PRINT_WORD.size();
        } else if(std::isdigit(inputFilrString[pos])) {
            std::string num;
            while(std::isdigit(inputFilrString[pos])) {
                num.push_back(inputFilrString[pos]);
                pos++;
            }
            tokenList.push_back({TokenType::KwInt, num});
        }

        switch (inputFilrString[pos]) {
            case '(':
                tokenList.push_back({TokenType::PrentacisIsOpen, StringTokens.at(TokenType::PrentacisIsOpen)});
                break;
            case '+':
                tokenList.push_back({TokenType::OpAdd, StringTokens.at(TokenType::OpAdd)});
                break;
            case '-':
                tokenList.push_back({TokenType::OpSubtruct, StringTokens.at(TokenType::OpSubtruct)});
                break;
            case '*':
                tokenList.push_back({TokenType::OpMultiply, StringTokens.at(TokenType::OpMultiply)});
                break;
            case ')':
                tokenList.push_back({TokenType::PrentacisIsClose, StringTokens.at(TokenType::PrentacisIsClose)});
                break;
            case ';':
                tokenList.push_back({TokenType::IsSemicolon, StringTokens.at(TokenType::IsSemicolon)});
                break;
        }
    }
    return tokenList;
}