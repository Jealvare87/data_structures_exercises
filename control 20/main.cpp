#include "BigVector.h"
#include <iostream>
#include <string>
using namespace std;

bool leeVector(BigVector& v) {
	if (cin.peek() == '(') {
		char sep;
		cin >> sep;
		while (cin.peek() != ')') {
			unsigned int i;
			double val;
			cin >> i >> sep >> val;
			if (cin.peek() != ')') {
				cin >> sep;
			}
			v.ponValor(i, val);
		}
		cin >> sep;
		return true;
	}
	else return false;
}
void saltaLinea() {
	string s;
	getline(cin, s);
}

int main() {
	bool fin = false;
	while (! fin) {
		BigVector v1;
		BigVector v2;
		if (leeVector(v1)) {
			leeVector(v2);
			saltaLinea();
			cout << v1.productoEscalar(v2) << endl;
		}
		else { 
			fin = true; 
		}
	}
}