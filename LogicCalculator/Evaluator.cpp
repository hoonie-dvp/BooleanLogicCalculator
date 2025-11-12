#include "Evaluator.h"
#include <stack>
#include <unordered_map>
#include <iostream>
#include <iomanip>

using namespace std;

Evaluator::Evaluator(const vector<Token>& tokens) : postfixTokens(tokens) {}

bool Evaluator::applyOperator(const string& op, bool a, bool b) {
    if (op == "and") return a && b;
    if (op == "or")  return a || b;
    if (op == "xor") return (a && !b) || (!a && b);
    return false;
}

bool Evaluator::applyUnaryOperator(const string& op, bool a) {
    if (op == "not") return !a;
    return a;
}

void Evaluator::evaluateTruthTable() {
    // Header
    cout << left << setw(3) << "a" << setw(3) << "b" << setw(3) << "c" << " | ";
    for (const auto& t : postfixTokens)
        if (t.type == TokenType::OPERATOR)
            cout << setw(7) << t.value;
    cout << " | Result\n";
    cout << "-------------------------------------------\n";

    for (int i = 0; i < 8; ++i) {
        bool a = (i & 4) >> 2;
        bool b = (i & 2) >> 1;
        bool c = (i & 1);
        unordered_map<string, bool> values = { {"a",a}, {"b",b}, {"c",c} };

        stack<bool> st;
        vector<bool> intermediates;

        for (auto& t : postfixTokens) {
            if (t.type == TokenType::INPUT) {
                st.push(values[t.value]);
            }
            else if (t.type == TokenType::OPERATOR) {
                if (t.value == "not") {
                    if (st.empty()) { cerr << "Error: Not enough operands for NOT\n"; return; }
                    bool val = st.top(); st.pop();
                    bool res = applyUnaryOperator(t.value, val);
                    st.push(res);
                    intermediates.push_back(res);
                }
                else {
                    if (st.size() < 2) { cerr << "Error: Not enough operands for " << t.value << "\n"; return; }
                    bool val2 = st.top(); st.pop();
                    bool val1 = st.top(); st.pop();
                    bool res = applyOperator(t.value, val1, val2);
                    st.push(res);
                    intermediates.push_back(res);
                }
            }
        }

        bool finalResult = st.top();

        // Ãâ·Â
        cout << setw(3) << a << setw(3) << b << setw(3) << c << " | ";
        for (auto val : intermediates) cout << setw(7) << val;
        cout << " | " << finalResult << "\n";
    }
}
