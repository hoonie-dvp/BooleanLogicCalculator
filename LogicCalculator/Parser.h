#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "Token.h"

using namespace std;

class Parser {
public:
	Parser(const vector<Token>& tokens);
	//Constructor : store token vector from Lexer

	~Parser();
	//Destructor

	vector<Token> getPostfix();

private:
	vector<Token> tokens;
	vector<Token> output;//Store postfix expression
	stack<Token> opStack; //Operator stack

	int getPrecedence(const string& op); //Get operator precedence
	bool isRightAssociative(const string& op);
	//Check if operator is right associative
	bool isOperator(const Token& token);
	//Check if token is operator
};