#pragma once
#include <map>
#include <string>
#include <vector>
#include <stack>

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
};

class Token {
public:
    bool operator==(Token other) const {
        return this->type == other.type && this->value == other.value;
    }
    TokenType type;
    std::string value;
};

class Tokanizer {
public:
    std::map<TokenType, std::string> StringTokens {
    {TokenType::Unknown, "error"},

    {TokenType::PrentacisIsOpen, "("},
    {TokenType::PrentacisIsClose, ")"},
    {TokenType::IsSemicolon, ";"},

    {TokenType::OpAdd, "+"},
    {TokenType::OpSubtruct, "-"},
    {TokenType::OpMultiply, "*"},
    {TokenType::OpDivide, "/"},

    {TokenType::KwPrint, "print"},
    {TokenType::KwInt, "int"},
    {TokenType::KwChar, "char"},
    };

    std::vector<Token> tokanize(std::string& inputFilrString);
};
