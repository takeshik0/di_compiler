#include <cctype>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <stack>

#include "AsmCode.hpp"
#include "Parser.hpp"


int main(int argc, char** argv) {
    
    std::ifstream inputFile("first_goal.txt");

    std::string temp_line;
    std::string inputFilrString;
    while (getline(inputFile, temp_line)) {
        inputFilrString += temp_line;
    }
    inputFile.close();
    Tokanizer tokanizer;
    std::vector<Token> tokenList = tokanizer.tokanize(inputFilrString);

    Parser parser;
    tokenList = parser.parseExpression(tokenList);

    std::transform(tokenList.begin(), tokenList.end(),
                   std::ostream_iterator<std::string>(std::cout, " "),
                   [](const auto &value) { return value.value; });

    AsmCode converter;
    codeMap asmCode = converter.convertToAsm(tokenList);
    converter.writeCodeToFile(asmCode);
    
    std::cout << "\n";
    std::system("nasm -f elf32 -o di.o di.asm"); 
    std::system("ld -m elf_i386 -o di di.o");
    std::system("./di");
    std::cout << "\n";
};