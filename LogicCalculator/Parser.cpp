#include "Parser.h"
#include <stack>

using namespace std;

Parser::Parser(const vector<Token>& tokens) : infixTokens(tokens) {}

bool Parser::isOperator(const Token& token) {
    if (token.type != TokenType::OPERATOR) return false;
    string op = token.value;
    return (op == "and" || op == "or" || op == "not" || op == "xor");
}

bool Parser::isUnaryOperator(const Token& token) {
    return token.type == TokenType::OPERATOR && token.value == "not";
}

int Parser::getPrecedence(const string& op) {
    if (op == "not") return 3;
    if (op == "and") return 2;
    if (op == "or") return 1;
    if (op == "xor") return 1;
    return 0;
}

bool Parser::isRightAssociative(const string& op) {
    return op == "not";
}

vector<Token> Parser::toPostfix() {
    vector<Token> output;
    stack<Token> opStack;

    for (const auto& token : infixTokens) {
        if (token.type == TokenType::INPUT) {
            output.push_back(token);
        }
        else if (isOperator(token)) {
            if (isUnaryOperator(token)) {
                while (!opStack.empty() && isOperator(opStack.top()) &&
                    getPrecedence(opStack.top().value) > getPrecedence(token.value)) {
                    output.push_back(opStack.top());
                    opStack.pop();
                }
                opStack.push(token);
            }
            else { // ÀÌÇ×
                while (!opStack.empty() && isOperator(opStack.top()) &&
                    ((isRightAssociative(token.value) && getPrecedence(token.value) < getPrecedence(opStack.top().value)) ||
                        (!isRightAssociative(token.value) && getPrecedence(token.value) <= getPrecedence(opStack.top().value)))) {
                    output.push_back(opStack.top());
                    opStack.pop();
                }
                opStack.push(token);
            }
        }
        else if (token.type == TokenType::PARREN_LEFT) {
            opStack.push(token);
        }
        else if (token.type == TokenType::PARREN_RIGHT) {
            while (!opStack.empty() && opStack.top().type != TokenType::PARREN_LEFT) {
                output.push_back(opStack.top());
                opStack.pop();
            }
            if (!opStack.empty() && opStack.top().type == TokenType::PARREN_LEFT)
                opStack.pop();
        }
    }

    while (!opStack.empty()) {
        output.push_back(opStack.top());
        opStack.pop();
    }

    return output;
}
