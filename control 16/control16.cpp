#include <iostream>
using namespace std;
#include <string>

#include "lista.h"
#include "Pila.h"

bool esVocal(char c) {
	return (tolower(c) == 'a' || tolower(c) == 'e' || tolower(c) == 'i' || tolower(c) == 'o' || tolower(c) == 'u');
}


void invierteSecuenciasNoVocales(Lista<char> &mensaje) {

	Lista<char>::Iterator iter = mensaje.begin();
	Lista<char>::Iterator iter_dos = mensaje.begin();
	Pila<char> pila;

	while (iter != mensaje.end() && iter_dos != mensaje.end()) {
		if (!esVocal(iter_dos.elem())) {
			pila.apila(iter_dos.elem());
			iter_dos.next();
		}
		else {
			if (iter.elem() != iter_dos.elem()) {
				iter.set(pila.cima());
				pila.desapila();
				iter.next();
			}
			else {
				iter_dos.next();
				iter.next();
			}
		}
	}

	while (!pila.esVacia()) {
		iter.set(pila.cima());
		pila.desapila();
		iter.next();
	}
}


// Imprime la lista por la salida estandar
void imprime(const Lista<char>& l) {
	Lista<char>::ConstIterator it = l.cbegin();
	while (it != l.cend()) {
		cout << it.elem();
		it.next();
	}
	cout << endl;
}


// Codifica el mensaje
void codifica(Lista<char>& mensaje) {
	invierteSecuenciasNoVocales(mensaje);
	mensaje.enredar();    // Esta operacion debe ser implementada como
						  // un nuevo metodo de Lista
}

// Transforma la linea en una lista de caracteres
void construyeMensaje(const string& linea, Lista<char>& mensaje) {
	for (unsigned int i = 0; i < linea.size(); i++)
		mensaje.pon_final(linea[i]);
}

int main() {
	string linea;
	while (getline(cin, linea)) {
		Lista<char> mensaje;
		construyeMensaje(linea, mensaje);
		codifica(mensaje);
		imprime(mensaje);
	}
	return 0;
}