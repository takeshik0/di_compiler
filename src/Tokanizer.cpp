#include "Tokanizer.hpp"
#include <cctype>
#include <vector>
std::vector<Token> Tokanizer::tokanize(std::string &inputFilrString) {

  std::vector<Token> tokenList;
  for (int pos = 0; pos < inputFilrString.size(); pos++) {
    if (std::isspace(inputFilrString[pos]) || inputFilrString[pos] == '\n') {
      continue;
    }

    const auto PRINT_WORD = StringTokens.at(TokenType::KwPrint);
    const auto INT_WORD = StringTokens.at(TokenType::IntVariable);
    if (inputFilrString.compare(pos, PRINT_WORD.size(), PRINT_WORD) == 0) {
      tokenList.push_back({TokenType::KwPrint, PRINT_WORD});
      pos += PRINT_WORD.size();
    } else if (inputFilrString.compare(pos, INT_WORD.size(), INT_WORD) == 0) {
      tokenList.push_back({TokenType::IntVariable, INT_WORD});
      pos += INT_WORD.size();

      std::string variable = "";
      while (inputFilrString[pos] != ';') {
        if (!std::isspace(inputFilrString[pos])) {
          variable.push_back(inputFilrString[pos]);
        }
        pos++;
      }
      tokenList.push_back({TokenType::IntegerValue, variable});
    } else if (isValidVariableSymbol(inputFilrString[pos])) {
      std::string variable = "";
      while (isValidVariableSymbol(inputFilrString[pos])) {
        variable.push_back(inputFilrString[pos]);
        pos++;
      }
      tokenList.push_back({TokenType::IntegerValue, variable});
    }
    switch (inputFilrString[pos]) {
    case '(':
      tokenList.push_back({TokenType::PrentacisIsOpen,
                           StringTokens.at(TokenType::PrentacisIsOpen)});
      break;
    case '+':
      tokenList.push_back(
          {TokenType::OpAdd, StringTokens.at(TokenType::OpAdd)});
      break;
    case '-':
      tokenList.push_back(
          {TokenType::OpSubtruct, StringTokens.at(TokenType::OpSubtruct)});
      break;
    case '*':
      tokenList.push_back(
          {TokenType::OpMultiply, StringTokens.at(TokenType::OpMultiply)});
      break;
    case '/':
      tokenList.push_back(
          {TokenType::OpDivide, StringTokens.at(TokenType::OpDivide)});
      break;
    case ')':
      tokenList.push_back({TokenType::PrentacisIsClose,
                           StringTokens.at(TokenType::PrentacisIsClose)});
      break;
    case ';':
      tokenList.push_back(
          {TokenType::IsSemicolon, StringTokens.at(TokenType::IsSemicolon)});
      break;
    }
  }
  return tokenList;
}

bool Tokanizer::isValidVariableSymbol(char symbol) {
  if ((symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z')) {
    return true;
  }
  return false;
}