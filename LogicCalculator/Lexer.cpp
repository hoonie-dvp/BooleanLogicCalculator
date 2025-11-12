#include "Lexer.h"
#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

Lexer::Lexer(string& logicExpression) : lexExpression(logicExpression) {}

Lexer::~Lexer() {}
bool Lexer::isOperator(const string& word) {
	return word == "and" || word == "or" || word == "not" || word == "xor";
}
//Error handling: vecter<Token> is the type of return value
vector<Token> Lexer::tokenize() {
	int getLogicLength = lexExpression.length();

	//Temporary variable to store the empty space
	string temp;
	for (int i = 0; i < getLogicLength;i++) {

		char c = lexExpression[i];
		//check for empty space
		if (isspace(c)) {
			continue;
		}
			
		if (c == '(') {
			tokens.push_back(Token(TokenType::PARREN_LEFT, "(" ));
			i++;
			continue;
		}
		if (c == ')') {
			tokens.push_back(Token(TokenType::PARREN_RIGHT, ")"));
			i++;
			continue;
		}

		if (isalpha(c)) {
			string getWord;
			while(i<getLogicLength && isalpha(lexExpression[i])) {
				//Error handling: static_cast to avoid sign extension issues
				getWord += tolower(static_cast<unsigned char>(lexExpression[i]));
				i++;
			}
			
			if (isOperator(getWord)) {
				tokens.push_back(Token(TokenType::OPERATOR, getWord));
			}
			else {
				tokens.push_back(Token(TokenType::INPUT, getWord));
			}
		}
	}
	return tokens;
}