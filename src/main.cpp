#include <atomic>
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <memory>
#include <unordered_map>

#include "Tokanizer.hpp"



using AsmCode = std::unordered_map<std::string, std::vector<std::string>>;

void calcExpression(std::vector<Token>::iterator& it, AsmCode& asm_code, std::string& currOperator) {
    while (it->type != TokenType::PrentacisIsClose) {
        if (it->type == TokenType::KwInt) {
            asm_code["_start:"].push_back(currOperator + " eax, " + it->value);
            //std::cout << _start.back();
        }
        if (it->type == TokenType::OpAdd){
            currOperator = "add";
        }
        else if (it->type == TokenType::OpSubtruct) {
            currOperator = "sub";
        }
        else if (it->type == TokenType::PrentacisIsOpen) {
            ++it;
            calcExpression(it, asm_code, currOperator);
        }
        ++it;
    }
}

int main(int argc, char** argv) {
    
    std::ifstream inputFile("first_goal.txt");

    std::string temp_line;
    std::string inputFilrString;
    while (getline(inputFile, temp_line)) {
        inputFilrString += temp_line;
    }
    inputFile.close();

    std::vector<Token> tokenList = tokanize(inputFilrString);

    std::transform(tokenList.begin(), tokenList.end(),
                   std::ostream_iterator<std::string>(std::cout, " "),
                   [](const auto &value) { return value.value; });

    AsmCode asm_code;

    //std::vector<std::string, std::vector<std::string>> asm_code;
    

    asm_code["section .text"] = {"\n\tglobal _start\n"};
    asm_code["_start:"] = {""};
    asm_code["section .data"] = {""};
    asm_code["convert_to_ascii:"] = {""};  
    asm_code["positive:"] = {""}; 

    std::string currOperator = "mov";
    for (auto it = tokenList.begin(); it != tokenList.end(); ++it)
    {

        if(it->type == TokenType::KwPrint) {
            asm_code["section .data"].push_back("result db ' ', '0', 0xA");
            ++it;

            if (it->value == "(") {
                ++it;
                calcExpression(it, asm_code, currOperator);
            }

            asm_code["_start:"].push_back("cmp eax, 0");
            asm_code["_start:"].push_back("jge positive");
            asm_code["_start:"].push_back("neg eax");
            asm_code["_start:"].push_back("mov byte [result], '-'");
            asm_code["_start:"].push_back("jmp convert_to_ascii");

            asm_code["positive:"].push_back("mov byte [result], ' '");

            asm_code["convert_to_ascii:"].push_back("add eax, '0'");
            asm_code["convert_to_ascii:"].push_back("mov [result + 1], al");
            asm_code["convert_to_ascii:"].push_back("mov eax, 4");
            asm_code["convert_to_ascii:"].push_back("mov ebx, 1");
            asm_code["convert_to_ascii:"].push_back("mov ecx, result");
            asm_code["convert_to_ascii:"].push_back("mov edx, 3");
            asm_code["convert_to_ascii:"].push_back("int 0x80");

            asm_code["convert_to_ascii:"].push_back("    mov eax, 1");
            asm_code["convert_to_ascii:"].push_back("xor ebx, ebx");
            asm_code["convert_to_ascii:"].push_back("int 0x80");

        }
    }

    std::ofstream asm_file("di.asm");
    
    std::vector<std::string> sortedKeys;

    for (const auto &it : asm_code) {
        for (const auto &key : sortedKeys) {
            
        }
    }
    
    for (const auto &key : asm_code) {
        asm_file << key.first;
        for (const auto& contains : key.second) {
            if (contains != key.second.back()) {
                asm_file << contains + "\n\t";
            } else {
                asm_file << contains + "\n";
            }
        }
    }

    
    asm_file.close();

    std::system("nasm -f elf32 -o di.o di.asm"); 
    std::system("ld -m elf_i386 -o di di.o");
    std::system("./di");


};