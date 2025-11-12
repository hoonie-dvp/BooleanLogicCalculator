#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Evaluator.h"

using namespace std;

int main() {
    string expr;
    cout << "Enter logical expression using a,b,c and operators (and, or, not, xor): ";
    getline(cin, expr);

    Lexer lexer(expr);
    vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    vector<Token> postfix = parser.toPostfix();

    Evaluator eval(postfix);
    eval.evaluateTruthTable();

    return 0;
}
