#include "AsmCode.hpp"
#include "Tokanizer.hpp"
#include <iostream>
#include <string>

std::string  AsmCode::getOperator(std::vector<Token>::iterator& element) {
    std::string tempOperator;
    switch (element->type) {
            case TokenType::OpAdd:
                tempOperator = "add";
                break;
            case TokenType::OpSubtruct:
                tempOperator = "sub";
                break;
            case TokenType::OpMultiply:
                tempOperator = "imul";
                break;
            case TokenType::OpDivide:
                tempOperator = "idiv";
                break;
        }
    return tempOperator;
}

std::string AsmCode::calculateExpression(std::vector<Token>::iterator& currentElement, codeMap& asmCode) {
    std::string currOperator = "mov";
    std::stack<int> operands;

    while (currentElement->type != TokenType::PrentacisIsClose) {
        if(currentElement->type == TokenType::IntegerValue) {
            operands.push(std::stoi(currentElement->value));
        } else {
            int firstOrderValue = operands.top();
            operands.pop();
            int secondOrderValue = operands.top();
            operands.pop();
            switch (currentElement->type) {
                case TokenType::OpAdd:
                    operands.push(secondOrderValue + firstOrderValue);
                    break;
                case TokenType::OpSubtruct:
                    operands.push(secondOrderValue - firstOrderValue);
                    break;
                case TokenType::OpMultiply:
                    operands.push(secondOrderValue * firstOrderValue);
                    break;
                case TokenType::OpDivide:
                    operands.push(secondOrderValue / firstOrderValue);
                    break;
            }
        }
        ++currentElement;
    }
    if(!operands.empty()) {
        return std::to_string(operands.top());
    }
    return nullptr;
}

codeMap AsmCode::convertToAsm(std::vector<Token>& tokenList) {
    codeMap asmCode;
    asmCode["section .text"] = {"\n\tglobal _start"};
    asmCode["_start:"] = {""};
    
    
    for (auto currentElement = tokenList.begin(); currentElement != tokenList.end(); ++currentElement)
    {
        if(currentElement->type == TokenType::KwPrint) {
            
            //asmCode["section .bss"] = {""};
            //asmCode["section .bss"].push_back("buffer resb 12");
            //keysOrder.emplace_back("section .bss");

            
            ++currentElement;
            
            std::string msgToPrint = "";
            std::cout << msgToPrint << std::endl;
            if (currentElement->value == "(" ) {
                ++currentElement;
                if(currentElement->value == ")") {
                    msgToPrint = "";
                } else {
                    msgToPrint = calculateExpression(currentElement, asmCode);
                }
            }
            
            keysOrder.emplace_back("_start:");
            asmCode["_start:"].push_back("mov edx, " + std::to_string(msgToPrint.length()));
            asmCode["_start:"].push_back("mov ecx, result");
            asmCode["_start:"].push_back("mov ebx, 1");
            asmCode["_start:"].push_back("mov eax, 4");
            asmCode["_start:"].push_back("int 0x80");
            asmCode["_start:"].push_back("mov eax, 1");
            asmCode["_start:"].push_back("int 0x80");

            asmCode["section .data"] = {""};
            asmCode["section .data"].push_back("result db '" + msgToPrint + "', 0xA");
            keysOrder.emplace_back("section .data");
        }
    }
    return asmCode;
}

void AsmCode::writeCodeToFile(codeMap& asmCode) {

    std::ofstream asmFile("di.asm");
    
    for (const auto &key : keysOrder) {
        asmFile << key;
        for (const auto& contains : asmCode[key]) {
            if (contains != asmCode[key].back()) {
                asmFile << contains + "\n\t";
            } else {
                asmFile << contains + "\n";
            }
        }
    }
    
    asmFile.close();
}