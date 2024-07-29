#pragma once
#include "Tokanizer.hpp"
#include <fstream>
#include <unordered_map>
#include <vector>

using codeMap = std::unordered_map<std::string, std::vector<std::string>>;

class AsmCode {
private:
    std::vector<std::string> keysOrder = {"section .text"};
    std::string getOperator(std::vector<Token>::iterator& element);
public:
    std::string calculateExpression(std::vector<Token>::iterator& it, codeMap& asmCode);
    codeMap convertToAsm(std::vector<Token>& tokenList);
    void writeCodeToFile(codeMap& asmCode);
};
