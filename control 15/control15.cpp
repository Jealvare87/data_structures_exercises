#include <iostream>
#include "dcola.h"
using namespace std;

unsigned int afortunado(unsigned int n, unsigned int m) { //n>=1  m>=2 
	if (n == 1) {
		return n;
	}
	else {
		DCola<unsigned int> cola = DCola<unsigned int>();
		int contador = 1;
		for (unsigned int i = 0; i < n; i++) { // introduce datos
			cola.pon_final(i + 1);
		}
		while (cola.ultimo() != cola.primero()) {
			if (contador%m == 0) {
				for (int j = 0; j < m - 1; j) {
					cola.pon_ppio();
					cola.quita_ppio();
				}
			}
			contador++;
		}
		return cola.primero();
	}

}


int main() {
	int n, m;
	while ((cin >> n)) {
		cin >> m;
		cout << afortunado(n, m) << endl;
	}
	return 0;
}