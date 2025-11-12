#pragma once
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include "Token.h"

using namespace std;
class Evaluator {
public:
	Evaluator(const vector<Token>& Tokens);
	void evaluateTruthTable();
	//Display truth table for the expression as a result

private:
	vector<Token> postfixTokens;

	bool applyOperator(const string& op, bool a, bool b);
	bool applyUnaryOperator(const string& op, bool a);

};