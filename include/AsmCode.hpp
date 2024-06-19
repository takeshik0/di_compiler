#pragma once
#include "Tokanizer.hpp"
#include <fstream>
#include <unordered_map>

using codeMap = std::unordered_map<std::string, std::vector<std::string>>;

class AsmCode {
private:
    std::vector<std::string> keysOrder = {"section .text"};
    
public:
    void calculateExpression(std::vector<Token>::iterator& it, codeMap& asmCode, std::string& currOperator);
    codeMap convertToAsm(std::vector<Token>& tokenList);
    void writeCodeToFile(codeMap& asmCode);
};
