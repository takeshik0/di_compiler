#pragma once
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

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

struct Token {
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
