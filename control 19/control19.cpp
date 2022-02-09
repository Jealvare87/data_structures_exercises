#include <iostream>
#include <string>
#include "diccionario.h"
#include "lista.h"
using namespace std;


// Clase Puntuacion. Sirve para representar la puntuacion final  (nota)
// obtenida por un alumno.
class Puntuacion {
public:
	string alumno;
	int nota;
	Puntuacion(const string& nombre, int puntuacion) : alumno(nombre), nota(puntuacion) {}
};

void califica(const Lista<string>& bien, const Lista<string>& mal, Lista<Puntuacion>& listado) {
	Diccionario<string, int> s;
	Lista<string>::ConstIterator i = bien.cbegin();
	Lista<string>::ConstIterator l = mal.cbegin();

	while (l != mal.cend()) { // Los que están mal
		if (s.contiene(l.elem())) {
			int aux = s.valorPara(l.elem());
			aux -= 1;
			s.inserta(l.elem(), aux);
		}
		else {
			s.inserta(l.elem(), -1);
		}
		l.next();
	}

	while (i != bien.cend()) { // Los que están bien
		if (s.contiene(i.elem())) {
			int aux = s.valorPara(i.elem());
			aux += 1;
			s.inserta(i.elem(), aux);
		}
		else {
			s.inserta(i.elem(), 1);
		}
		i.next();
	}

	Diccionario<string, int>::ConstIterator it = s.cbegin();

	while (it != s.cend()) {
		Puntuacion aux = Puntuacion(it.clave(), it.valor());
		if (aux.nota != 0) {
			listado.pon_final(aux);
		}
		it.next();
	}

}

void imprimePuntuaciones(Lista<Puntuacion>& listado) {
	Lista<Puntuacion>::ConstIterator i = listado.cbegin();
	Lista<Puntuacion>::ConstIterator e = listado.cend();
	while (i != e) {
		cout << "[" << i.elem().alumno << ":" << i.elem().nota << "]";
		i.next();
	}
	cout << endl;
}

void leeResultados(Lista<string>& bien, Lista<string>& mal) {
	string nombre;
	do {
		cin >> nombre;
		if (nombre != "#") {
			string resultado;
			cin >> resultado;
			if (resultado == "+")
				bien.pon_final(nombre);
			else
				mal.pon_final(nombre);
		}
	} while (nombre != "#");
}

int main() {
	string comienzo;
	while (cin >> comienzo) {
		Lista<string> bien;
		Lista<string> mal;
		Lista<Puntuacion> listado;
		leeResultados(bien, mal);
		califica(bien, mal, listado);
		imprimePuntuaciones(listado);
	}
	return 0;
}