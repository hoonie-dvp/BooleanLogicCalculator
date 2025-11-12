#include <iostream>
#include <vector>
#include <string>
#include "Lexer.h"

using namespace std;

int main() {
	string expression;
	int x, y, z;

	cout << "Enter initial value of three inputs(0/1)" << endl;
	cin >> x >> y >> z;

	if(x > 1 || y > 1 || z > 1 || x < 0 || y < 0 || z < 0) 
		cerr << "Invalid Input! Please enter 0 or 1 only." << endl;
		return 1;

	cin.ignore(); // To ignore the newline character after reading integers => important for getline to work properly => Remove input buffer issues
	cout << "Enter three inputs logical expression using operators(and, or , not, xor): ";
	getline(cin, expression);

	Lexer input(expression);
	

}