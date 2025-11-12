#include "Parser.h"
#include <iostream>

using namespace std;

//Use Shunting Yard Algorithm to convert infix to postfix

Parser::Parser(const vector<Token>& tokens) : tokens(tokens) {}

Parser::~Parser() {}

bool Parser::isOperator(const Token& token) {
	if(token.type != TokenType::OPERATOR){
		return false;
	}
	string op = token.value;
	return (op == "and" || op == "or" || op == "not" || op == "xor");
}

int Parser::getPrecedence(const string& op) {
	if (op == "not") return 3;
	if (op == "and") return 2;
	if (op == "or" || op == "xor") return 1;
	return 0;
}

bool Parser :: isRightAssociative(const string& op) {
	return op == "not";
}

vector<Token> Parser::getPostfix() {
	for (const Token& token : tokens) {
		if (token.type == TokenType::INPUT) {
			output.push_back(token);
		}

		else if (isOperator(token)) {
			while (!opStack.empty()) {
				Token topOp = opStack.top();
				if (!isOperator(topOp)) {
					break;
				}
				int topPrec = getPrecedence(topOp.value);
				int currPrec = getPrecedence(token.value);

				bool rightAssoc = isRightAssociative(token.value);

				if ((!rightAssoc && currPrec <= topPrec) || (rightAssoc && currPrec < topPrec)) {
					output.push_back(topOp);
					opStack.pop();
				}else {
					break;
				}

			}
			opStack.push(token);
		}

		else if (token.type == TokenType::PARREN_LEFT) {
			opStack.push(token);
		}

		else if (token.type == TokenType::PARREN_RIGHT) {
			while (!opStack.empty() && opStack.top().type != TokenType::PARREN_LEFT) {
				output.push_back(opStack.top());
				opStack.pop();
			}

			if (!opStack.empty() && opStack.top().type == TokenType::PARREN_LEFT) {
				opStack.pop();
			}
		}
	}
	while (!opStack.empty()) {
		output.push_back(opStack.top());
		opStack.pop();
	}

	return output;

}
