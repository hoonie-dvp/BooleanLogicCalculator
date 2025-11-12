#pragma once
#include <vector>
#include <string>
#include "Token.h"

class Parser {
private:
    std::vector<Token> infixTokens;

    int getPrecedence(const std::string& op);
    bool isRightAssociative(const std::string& op);
    bool isOperator(const Token& token);
    bool isUnaryOperator(const Token& token);

public:
    Parser(const std::vector<Token>& tokens);
    std::vector<Token> toPostfix();
};
