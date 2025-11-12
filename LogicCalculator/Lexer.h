#pragma once
#include "Token.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Lexer {
public:
	Lexer(string& logicExpression);
	~Lexer();
	//Tokenize the input logical expression into tokens with valid types in Enum
	vector<Token> tokenize();

	bool isOperator(const string& word);

private:
	string lexExpression;
	vector<Token> tokens;
};