#include "AsmCode.hpp"

void AsmCode::calculateExpression(std::vector<Token>::iterator& it, codeMap& asmCode, std::string& currOperator) {
    while (it->type != TokenType::PrentacisIsClose) {
        switch (it->type) {
            case TokenType::KwInt:
                asmCode["_start:"].push_back(currOperator + " eax, " + it->value);
                break;
            case TokenType::OpAdd:
                currOperator = "add";
                break;
            case TokenType::OpSubtruct:
                currOperator = "sub";
                break;
            case TokenType::OpMultiply:
                currOperator = "imul";
                break;
            case TokenType::PrentacisIsOpen:
                ++it;
                calculateExpression(it, asmCode, currOperator);
                break;
            case TokenType::Unknown:
            case TokenType::PrentacisIsClose:
            case TokenType::IsSemicolon:
            case TokenType::OpDivide:
            case TokenType::KwPrint:
            case TokenType::KwChar:
              break;
            }
        ++it;
    }
}

codeMap AsmCode::convertToAsm(std::vector<Token>& tokenList) {
    codeMap asmCode;
    asmCode["section .text"] = {"\n\tglobal _start"};
    asmCode["_start:"] = {""};
    keysOrder.emplace_back("_start:");
    std::string currOperator = "mov";
    for (auto it = tokenList.begin(); it != tokenList.end(); ++it)
    {
        if(it->type == TokenType::KwPrint) {
            
            asmCode["section .bss"] = {""};
            asmCode["section .bss"].push_back("buffer resb 12");
            keysOrder.emplace_back("section .bss");

            asmCode["section .data"] = {""};
            asmCode["section .data"].push_back("result db ' ', '0', 0xA");
            keysOrder.emplace_back("section .data");
            ++it;

            if (it->value == "(") {
                ++it;
                calculateExpression(it, asmCode, currOperator);
            }
            asmCode["_start:"].push_back("cmp eax, 0");
            asmCode["_start:"].push_back("jge positive");
            asmCode["_start:"].push_back("neg eax");
            asmCode["_start:"].push_back("mov byte [result], '-'");
            asmCode["_start:"].push_back("jmp convert_loop");
            asmCode["positive:"] = {""};            
            asmCode["positive:"].push_back("mov edi, buffer + 12");
            asmCode["positive:"].push_back("mov ebx, 10");
            keysOrder.emplace_back("positive:");

            asmCode["convert_loop:"] = {""};
            keysOrder.emplace_back("convert_loop:");
            asmCode["convert_loop:"].push_back("xor edx, edx");
            asmCode["convert_loop:"].push_back("div ebx");
            asmCode["convert_loop:"].push_back("add dl, '0'");
            asmCode["convert_loop:"].push_back("dec edi");
            asmCode["convert_loop:"].push_back("mov [edi], dl");
            asmCode["convert_loop:"].push_back("test eax, eax");
            asmCode["convert_loop:"].push_back("jnz convert_loop");
            asmCode["convert_loop:"].push_back("mov eax, buffer + 12");
            asmCode["convert_loop:"].push_back("sub eax, edi");
            asmCode["convert_loop:"].push_back("mov edx, eax");
            asmCode["convert_loop:"].push_back("mov ecx, edi");
            asmCode["convert_loop:"].push_back("cmp byte [result], '-'");
            asmCode["convert_loop:"].push_back("jne print_number");
            asmCode["convert_loop:"].push_back("mov eax, 4");
            asmCode["convert_loop:"].push_back("mov ebx, 1");
            asmCode["convert_loop:"].push_back("lea ecx, [result]");
            asmCode["convert_loop:"].push_back("mov edx, 1");
            asmCode["convert_loop:"].push_back("int 0x80");

            asmCode["print_number:"] = {""};
            keysOrder.emplace_back("print_number:");
            asmCode["print_number:"].push_back("mov eax, 4");
            asmCode["print_number:"].push_back("mov ebx, 1");
            asmCode["print_number:"].push_back("int 0x80");
            asmCode["print_number:"].push_back("\tmov eax, 1");
            asmCode["print_number:"].push_back("xor ebx, ebx");
            asmCode["print_number:"].push_back("int 0x80");
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