/*
Define a token structure to represent different types of tokens in a logic calculator.
*/

#pragma once
#include <string>

using namespace std;

enum class TokenType {
	INPUT, OPERATOR, PARREN_LEFT, PARREN_RIGHT
};

struct Token {
	TokenType type;
	std::string value;

	//Constructor for vector initialization
	Token(TokenType t, const string& v) : type(t), value(v) {}
};									    