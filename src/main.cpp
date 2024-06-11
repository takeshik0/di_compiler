#include <atomic>
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <iterator>

enum class TokenType {
    Unknown,

    PrentacisIsOpen,
    PrentacisIsClose,
    IsSemicolon,

    OpAdd,
    OpSubtruct,
    OpMultiply,
    OpDivide,
    

    KwPrint,
    KwInt,
    KwChar,


    Count
};

std::map<TokenType, std::string> StringTokens {
    {TokenType::Unknown, "error"},

    {TokenType::PrentacisIsOpen, "("},
    {TokenType::PrentacisIsClose, ")"},
    {TokenType::IsSemicolon, ";"},

    {TokenType::OpAdd, "+"},
    {TokenType::OpSubtruct, "-"},
    {TokenType::OpMultiply, "OpMultiply"},
    {TokenType::OpDivide, "/"},

    {TokenType::KwPrint, "print"},
    {TokenType::KwInt, "int"},
    {TokenType::KwChar, "char"},
};

struct Token {
    TokenType type;
    std::string value;
};

std::vector<Token> tokanize(std::string& inputFilrString) {
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


void calcExpression(std::vector<Token>::iterator& it, std::vector<std::string>& _start, std::string& currOperator) {
    while (it->type != TokenType::PrentacisIsClose) {
        if (it->type == TokenType::KwInt) {
            _start.push_back(currOperator + " eax, " + it->value);
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
            calcExpression(it, _start, currOperator);
        }
        ++it;
    }
}

int main(int,char**) {
    
    std::ifstream inputFile("first_goal.txt");

    std::string temp_line;
    std::string inputFilrString;
    while (getline(inputFile, temp_line)) {
        inputFilrString += temp_line;
    }
    inputFile.close();

    //std::cout << inputFilrString;

    std::vector<Token> tokenList = tokanize(inputFilrString);

    std::transform(tokenList.begin(), tokenList.end(),
                   std::ostream_iterator<std::string>(std::cout, " "),
                   [](const auto &value) { return value.value; });

    std::vector<std::string> section_text = {"section .text\n\t", "global _start\n"};
    std::vector<std::string> _start = {"_start:"};
    std::vector<std::string> section_data = {"section .data"};  
    std::vector<std::string> convert_to_ascii = {"convert_to_ascii:"};

    std::string currOperator = "mov";
    for (std::vector<Token>::iterator it = tokenList.begin(); it != tokenList.end(); ++it)
    {

        if(it->type == TokenType::KwPrint) {
            std::string spaceForMsg = "'0'";
            section_data.push_back("result db " + spaceForMsg + ", 0xA");
            ++it;

            if (it->value == "(") {
                ++it;
                calcExpression(it, _start, currOperator);
            }

            //_start.push_back("mov ebx, 10");
            //_start.push_back("xor edx, edx");
            //_start.push_back("div ebx");

            //_start.push_back("add dl, '0'");
            //_start.push_back("mov [result + 1], dl");

            _start.push_back("cmp eax, 0");
            _start.push_back("mov [result + 1], dl");

            _start.push_back("add eax, '0'");
            _start.push_back("jge positive");

            convert_to_ascii.push_back("mov eax, 4");
            convert_to_ascii.push_back("mov ebx, 1");
            convert_to_ascii.push_back("mov ecx, result");
            convert_to_ascii.push_back("mov edx, 2");
            convert_to_ascii.push_back("int 0x80");
            convert_to_ascii.push_back("\tmov eax, 1");
            convert_to_ascii.push_back("xor ebx, ebx");
            convert_to_ascii.push_back("int 0x80");

        }
    }

    std::ofstream asm_file("di.asm");

    for(auto &it : section_text) {
        asm_file << it;
    }
    for(auto &it : _start) {
        if(it != _start.back()) {
            asm_file << it + "\n\t";
        }
        else {
            asm_file << it + "\n";
        }
        
    }
    for(auto &it : section_data) {
        if(it != _start.back()) {
            asm_file << it + "\n\t";
        }
        else {
            asm_file << it + "\n";
        }
    }

    for(auto &it : convert_to_ascii) {
        asm_file << it + "\n\t";
    }
    asm_file.close();

    std::system("nasm -f elf32 -o di.o di.asm"); 
    std::system("ld -m elf_i386 -o di di.o");
    std::system("./di");


};