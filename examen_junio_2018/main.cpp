#include <iostream>
#include "cola.h"
#include "arbin.h"
#include "DiccionarioHash.h"
#include "lista.h"
#include "pila.h"
#include "diccionario.h"
using namespace std;

int max(int x, int y) {
	if (x > y) return x;
	return y;
}

int caminoAux(const Arbin<int>& a, int &camino_max) {
	if (a.esVacio()) {
		return 0;
	}
	else {
		int iz = caminoAux(a.hijoIz(), camino_max);
		int der = caminoAux(a.hijoDer(), camino_max);
		int total = iz + der + 1;
		if (total > camino_max) {
			camino_max = total;
		}
		return max(iz, der) + 1;
	}
}

int caminoLargo(const Arbin<int>& a) {
	int max = 0;
	caminoAux(a, max);
	return max;
}


/*Septiembre 2017 - Segundo Cuatrimestre*/
/*Ejercicio 2.-*/
//Int max ya está declarado arriba

void mayorProfundidad(const Arbin<int>& a, const int k, int& mayores, int altura) {
	if (!a.esVacio()) {
		if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) if (altura > k) mayores++;
		else {
			if (!a.hijoIz().esVacio())mayorProfundidad(a.hijoIz(), k, mayores, altura + 1);
			if (!a.hijoDer().esVacio())mayorProfundidad(a.hijoDer(), k, mayores, altura + 1);
		}
	}
}

/*Ejercicio 3.-*/
class EConductorDuplicado {};
class EConductorInexistente {};

class CarnetPorPuntos {
public:
	/**/
	CarnetPorPuntos() {}

	/**/
	void nuevo(string DNI) {
		if (dni_puntos.contiene(DNI)) throw EConductorDuplicado();
		dni_puntos.inserta(DNI, 15);
	}

	/**/
	void quitar(string DNI, int puntos) {
		DiccionarioHash<string, int>::Iterator it = dni_puntos.busca(DNI);
		if (it == dni_puntos.end()) throw EConductorInexistente();
		int ptos_fin = it.valor() - puntos;
		ptos_fin < 0? it.setVal(0): it.setVal(ptos_fin);
	}

	/**/
	void recuperar(string DNI, int puntos) {
		DiccionarioHash<string, int>::Iterator it = dni_puntos.busca(DNI);
		if (it == dni_puntos.end()) throw EConductorInexistente();
		int ptos_fin = it.valor() + puntos;
		ptos_fin > 15 ? it.setVal(15) : it.setVal(ptos_fin);
	}

	/**/
	int consultar(string DNI) {
		DiccionarioHash<string, int>::ConstIterator it = dni_puntos.cbusca(DNI);
		if (it == dni_puntos.cend()) throw EConductorInexistente();
		return it.valor();
	}

	/**/
	int cuantos_con_puntos(int puntos) {
		int contador = 0;
		DiccionarioHash<string, int>::ConstIterator it = dni_puntos.cbegin();
		while (it != dni_puntos.cend()) {
			if (it.valor() == puntos)contador++;
			it.next();
		}
		return contador;
	}

	/**/

private:
	DiccionarioHash<string, int> dni_puntos;
	Lista<string> dnis_;
};

/*Examen Junio 2018 Sesion 1 - Ejercicio 2.-*/

int num_aux(const Arbin<char>& mapa, int monstruos, int&salvos) {
	if (mapa.esVacio()) return 0;
	else {
		if (mapa.raiz() == 'M') {
			return num_aux(mapa.hijoIz(), monstruos+1, salvos) + num_aux(mapa.hijoDer(), monstruos + 1, salvos);
		}
		else if (mapa.raiz() == 'D') {
			int a = num_aux(mapa.hijoIz(), monstruos, salvos) + num_aux(mapa.hijoDer(), monstruos, salvos);
			if (monstruos <= a)salvos++;
			return a;
		}
		else {
			return num_aux(mapa.hijoIz(), monstruos, salvos) + num_aux(mapa.hijoDer(), monstruos, salvos) + 1;
		}
	}
}

int num_a_salvo(const Arbin<char>& mapa) {
	int salvos = 0;
	num_aux(mapa, 0, salvos);
	return salvos;
}

/*Examen Junio 2018 Sesion 1 - Ejercicio 3.-*/

class EEcosistemaDuplicado {};
class EEcosistemaNoExiste {};

class ParqueNatural {
public:
	/**/
	ParqueNatural(){}

	/**/
	void an_ecosistema(string ecosistema) {
		if (_eco_especies.contiene(ecosistema)) throw EEcosistemaDuplicado();
		_eco_especies.inserta(ecosistema, DiccionarioHash<string, int>());
		_eco_nueesp.inserta(ecosistema, Lista<string>());
	}

	/**/
	void an_ejemplares(string ecosistema, string especie, int n) {
		DiccionarioHash<string, DiccionarioHash<string, int>>::Iterator it = _eco_especies.busca(ecosistema);
		Diccionario<string, int>::Iterator it2 = _esp_total.busca(especie);
		if (it == _eco_especies.end()) throw EEcosistemaNoExiste();

		// Insertar en las especies totales
		if (it2 == _esp_total.end()) {
			_esp_total.inserta(especie, n);
		}
		else {
			it2.setVal(it2.valor() + n);
		}

		//Insertar en las especies del ecosistema concreto
		DiccionarioHash<string, int>::Iterator it3 = it.valor().busca(especie);
		if (it3 == it.valor().end()) {
			it.valor().inserta(especie, n);
			_eco_nueesp.busca(ecosistema).valor().pon_ppio(especie); // Añadido al ecosistema una nueva especie
		}
		else {
			it3.setVal(it3.valor() + n);
		}
	}

	/**/
	Lista<string> lista_especies_ecosistema(string ecosistema, int n) {
		DiccionarioHash<string, Lista<string>>::ConstIterator it = _eco_nueesp.cbusca(ecosistema);
		if (it == _eco_nueesp.cend()) throw EEcosistemaNoExiste();
		int pos = 0;
		Lista<string> res;
		Lista<string>::ConstIterator it2 = it.valor().cbegin();
		while (it2 != it.valor().cend() && pos < n) {
			res.pon_final(it2.elem());
			it2.next();
			pos++;
		}
		return res;
	}

	/**/
	int numero_ejemplares_en_ecosistema(string ecosistema, string especie) {
		int res = 0;
		DiccionarioHash<string, DiccionarioHash<string, int>>::ConstIterator it = _eco_especies.cbusca(ecosistema);
		if (it == _eco_especies.cend()) throw EEcosistemaNoExiste();
		DiccionarioHash<string, int>::ConstIterator it2 = it.valor().cbusca(especie);
		res =  it2 !=  it.valor().cend()? it2.valor(): 0;
		return res;
	}

	/**/
	Lista<string> lista_especies_parque() {
		Lista<string> res;
		Diccionario<string, int>::ConstIterator it = _esp_total.cbegin();
		while (it != _esp_total.cend()) {
			res.pon_final(it.clave());
		}
		return res;
	}

	/**/
	int numero_ejemplares_en_parque(string especie) {
		Diccionario<string, int>::ConstIterator it = _esp_total.cbusca(especie);
		if (it == _esp_total.cend()) return 0;
		return it.valor();
	}

private:
	DiccionarioHash<string, DiccionarioHash<string, int>> _eco_especies;
	DiccionarioHash<string, Lista<string>> _eco_nueesp;
	Diccionario<string, int> _esp_total;
};


/*Examen 2018 Septiembre - Ejercicio 2.-*/

int num_aux(const Arbin<int> &a, int &curiosos, int altura) { // Cuenta nodos
	if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) return 1; //Hoja
	else {
		int iz = 0, der = 0;
		if (!a.hijoIz().esVacio())
			iz = num_aux(a.hijoIz(), curiosos, altura+1);
		if (!a.hijoDer().esVacio())
			der = num_aux(a.hijoDer(), curiosos, altura+1);
		if (a.raiz() == iz+altura) curiosos++;
		return iz+der+1; // hijoIz+hijoDer+raiz
	}
}

/*Examen 2018 Septiembre - Ejercicio 3.-*/

class EConciertoExistente {};
class EConciertoInexistente {};
class EClienteInexistente {};
class EAltaNoAdmitida {};
class EConciertoConEsperas {};
class EConciertoSinEsperas {};
class EEsperaNoAdmitida {};
class EAltaNoAdmitida {};

class SistemaVentas {
public:
	/**/
	SistemaVentas() {
		num_client = 0;
		num_conciert = 0;
	}

	/**/
	void an_concierto(string codigo_concierto) {
		if (_conc_client.contiene(codigo_concierto)) throw EConciertoExistente();
		_conc_client.inserta(codigo_concierto, Lista<string>());
		num_conciert++;
	}

	/**/
	void an_cliente(string codigo_cliente, string codigo_concierto) {
		/*
		DiccionarioHash<string, Lista<string>>::Iterator it =_conc_client.busca(codigo_concierto);
		Diccionario<string, string>::Iterator it2 = _client_conc.busca(codigo_cliente);
		if (it == _conc_client.end() 
			|| it2 == _client_conc.end() 
			|| it2.valor() == codigo_concierto) throw EAltaNoAdmitida();
		it.valor().pon_final(codigo_cliente);
		num_clientes++;
		*/
	}

	/**/
	void borra_concierto(string codigo_concierto) {
		DiccionarioHash<string, Lista<string>>::Iterator it = _conc_client.busca(codigo_concierto);
		if (it == _conc_client.end()) throw EConciertoInexistente();
		if (!it.valor().esVacia()) throw EConciertoConEsperas();
		_conc_client.borra(codigo_concierto);
	}

	/* O(n log n)*/
	void borra_cliente(string codigo_cliente) {
		Diccionario<string, string>::ConstIterator it = _client_conc.cbusca(codigo_cliente);
		if (it == _client_conc.cend()) throw EClienteInexistente();
		DiccionarioHash<string, Lista<string>>::Iterator it2 = _conc_client.busca(it.valor());
		Lista<string>::Iterator it3 = it2.valor().begin();
		while (it3.elem() != codigo_cliente && it3 != it2.valor().end()) it3.next();
		if (it3 != it2.valor().end()) it2.valor().eliminar(it3);
		_client_conc.borra(codigo_cliente);
	}

	/**/
	bool hay_clientes_en_espera(string codigo_concierto) {
		DiccionarioHash<string, Lista<string>>::ConstIterator it = _conc_client.cbusca(codigo_concierto);
		if (it == _conc_client.cend()) throw EConciertoInexistente();
		return !it.valor().esVacia();
	}

	/**/
	string proximo_cliente(string codigo_concierto) {
		DiccionarioHash<string, Lista<string>>::ConstIterator it = _conc_client.cbusca(codigo_concierto);
		if (it == _conc_client.cend()) throw EConciertoInexistente();
		return it.valor().esVacia()? throw EConciertoSinEsperas(): it.valor().primero();
	}


	/**/
	void venta(string codigo_concierto) {
		DiccionarioHash<string, Lista<string>>::Iterator it = _conc_client.busca(codigo_concierto);
		if (it == _conc_client.end()) throw EConciertoInexistente();
		if (it.valor().esVacia()) throw EConciertoSinEsperas();
		_client_conc.busca(it.valor().primero()).setVal("");
		it.valor().quita_ppio();
	}

	/**/
	void abandona(string codigo_cliente) {
		Diccionario<string, string>::Iterator it = _client_conc.busca(codigo_cliente);
		if (it == _client_conc.end()) throw EClienteInexistente();
		if (it.valor() != "") {
			DiccionarioHash<string, Lista<string>>::Iterator it2 = _conc_client.busca(it.valor());
			Lista<string>::Iterator it3 = it2.valor().begin();
			while (it3 != it2.valor().end()) it3.next();
			if (it3 != it2.valor().end()) it2.valor().eliminar(it3);
		}
		it.setVal("");
	}

	/**/
	void pon_en_espera(string codigo_cliente, string codigo_concierto) {
		/**/
	}

	/**/
	Lista<string>clientes() {
		Lista<string> res;
		Diccionario<string, string>::ConstIterator it = _client_conc.cbegin();
		while (it != _client_conc.cend()) {
			res.pon_final(it.clave());
			it.next();
		}
		return res;
	}
	
	/**/
	int num_clientes() {
		return num_client;
	}

	/**/
	int num_conciertos() {
		return num_conciert;
	}

private:
	DiccionarioHash <string, Lista<string>> _conc_client;
	Diccionario<string, string> _client_conc;
	int num_client;
	int num_conciert;
};

/*Examen Junio 2014 Segundo Cuatrimestre - Ejercio 2.-*/

int min(int x, int y) {
	if (x <= y) return x;
	return y;
}

int num_drag(const Arbin<string> &mapa, string &puerta, string &res) {
	if (!mapa.esVacio()) {
		if (mapa.hijoIz().esVacio() && mapa.hijoDer().esVacio()) { //Si es hoja
			puerta = mapa.raiz();
			return 0;
		}
		else {
			int iz = INT_MAX, der = INT_MAX; // Dudoso
			string p_iz = "", p_der = "";
			if (!mapa.hijoIz().esVacio()) iz = num_drag(mapa.hijoIz(), p_iz, res);
			if (!mapa.hijoDer().esVacio()) der = num_drag(mapa.hijoDer(), p_der, res);
			puerta = iz <= der? p_iz: p_der;
			int dragones = min(iz, der);
			if (mapa.raiz() == "Dragón")
				dragones++;
			else if (mapa.raiz() == "Tesoro")
				res = puerta;
			return dragones;
		}
	}
}

/*Examen 2015 Parcial - Ejercicio 2.-*/

void tiempoAux(const Arbin<char> &a, int&tiempo, int altura) {
	if (!a.esVacio()) {
		if(!a.hijoIz().esVacio())tiempoAux(a.hijoIz(), tiempo, altura+1);
		if(!a.hijoDer().esVacio())tiempoAux(a.hijoDer(), tiempo, altura+1);
		if (a.raiz() == 'X') tiempo += 2 * altura;
	}
}

int tiempoAyuda(const Arbin<char> &a) {
	int tiempo = 0;
	tiempoAux(a, tiempo, 0);
	return 0;
}

/**/
Lista<char> invierte(Lista<char>& in_list, int i, int k) {
	if (i >= (int)in_list.longitud() || i > k) {
		return in_list;
	}
	int contador = 0;
	Pila<char> b;
	Lista<char> res;
	while (!in_list.esVacia() && contador < i) {
		res.pon_final(in_list.primero());
		in_list.quita_ppio();
		contador++;
	}
	while (!in_list.esVacia() && contador < k+i) {
		b.apila(in_list.primero());
		in_list.quita_ppio();
		contador++;
	}
	while (!b.esVacia()) {
		res.pon_final(b.cima());
		b.desapila();
	}
	while (!in_list.esVacia()) {
		res.pon_final(in_list.primero());
		in_list.quita_ppio();
	}
	return res;
}

/**/
bool es_sim(const Arbin<int> &a, const Arbin<int> &b) {
	if (a.esVacio() && b.esVacio()) return true;
	if (a.esVacio()) return false;
	if (b.esVacio()) return false;

	return es_sim(a.hijoIz(), b.hijoDer()) && es_sim(a.hijoDer(), b.hijoIz());
}

bool esSimetrico(const Arbin<int> &a) {
	return es_sim(a.hijoIz(), a.hijoDer());
}

/**/
int max_alturita(int x, int y) {
	if (x >= y) return x;
	return y;
}
int camino_max(const Arbin<int> &a, int&cam_max) {
	if (a.esVacio()) return 0;
	else {

		int iz = camino_max(a.hijoIz(), cam_max);
		int der = camino_max(a.hijoDer(), cam_max);
		int total = iz+der+1;
		if (total > cam_max) cam_max = total;
		return max_alturita(iz,der)+1;
	}
}


typedef string IdAlumno;
typedef string IdAsignatura;
class Error_Faltas {};
class Faltas {
private:
	Diccionario<IdAlumno, int> alumno_total_faltas;
	DiccionarioHash<IdAsignatura, int> asignatura_total_faltas;
	DiccionarioHash<IdAsignatura, DiccionarioHash<IdAlumno, int>> asignatura_alumno_faltas;
	IdAsignatura max_faltas;
	int total_faltas;
public:
	/**/
	Faltas() {
		total_faltas = 0;
	}

	/**/
	void addAlumno(IdAlumno a) {
		if (alumno_total_faltas.contiene(a)) throw Error_Faltas();
		alumno_total_faltas.inserta(a, 0);
		DiccionarioHash<IdAsignatura, DiccionarioHash<IdAlumno, int>>::Iterator it = asignatura_alumno_faltas.begin();
		while (it != asignatura_alumno_faltas.end()) {
			it.valor().inserta(a, 0);
			it.next();
		}
	}

	/**/
	void addFalta(IdAlumno a, IdAsignatura b) {
		DiccionarioHash<IdAsignatura, DiccionarioHash<IdAlumno, int>>::Iterator it = asignatura_alumno_faltas.busca(b);
		Diccionario<IdAlumno, int>::Iterator it2 = alumno_total_faltas.busca(a);
		if (it == asignatura_alumno_faltas.end() || it2 == alumno_total_faltas.end()) throw Error_Faltas();
		it2.setVal(it2.valor() + 1);
		DiccionarioHash<IdAlumno, int>::Iterator it3 = it.valor().busca(a);	
		DiccionarioHash<IdAsignatura, int>::Iterator it4 = asignatura_total_faltas.busca(b);
		int total = it4.valor() + 1;
		it4.setVal(total);
		it3.setVal(it3.valor() + 1);
		if (total > total_faltas) {
			total_faltas = total;
			max_faltas = b;
		}
	}

	/**/
	void addAsignatura(IdAsignatura b) {
		if (!asignatura_total_faltas.contiene(b)) {
			asignatura_total_faltas.inserta(b, 0);
			asignatura_alumno_faltas.inserta(b, DiccionarioHash<IdAlumno, int>());
			auto it = asignatura_alumno_faltas.busca(b);
			auto it2 = alumno_total_faltas.cbegin();
			while (it2 != alumno_total_faltas.cend()) {
				it.valor().inserta(it2.clave(), 0);
				it2.next();
			}
		}
		else throw Error_Faltas();
	}

	/**/
	Lista<IdAlumno> noFaltas(){
		Lista<IdAlumno> res;
		Diccionario<IdAlumno, int>::ConstIterator it = alumno_total_faltas.cbegin();
		while (it != alumno_total_faltas.cend()) {
			if (it.valor() == 0) {
				res.pon_final(it.clave());
			}
			it.next();
		}
		return res;
	}

	/**/
	int totalFaltas(IdAlumno a) const{
		Diccionario<IdAlumno,int>::ConstIterator it = alumno_total_faltas.cbusca(a);
		if (it == alumno_total_faltas.cend()) throw Error_Faltas();
		return it.valor();
	}

	IdAsignatura maxFaltas() const {
		return max_faltas;
	}

};

/*Examen 2014 Septiembre 2º Parcial - Ejercicio 1.-*/

bool es_genealogico(const Arbin<int> &a) {
	if (!a.esVacio()) {
		if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) return true;
		bool b_iz = true, b_der = true;
		int iz = 0, der = 0;
		if (!a.hijoIz().esVacio()) {
			b_iz = es_genealogico(a.hijoIz());
			iz = a.hijoIz().raiz();
		}
		if (!a.hijoDer().esVacio()) {
			b_der = es_genealogico(a.hijoDer());
			der = a.hijoDer().raiz();
		}
		if ((a.raiz() + 18 < iz || a.raiz() + 18 < der) && b_iz && b_der) {
			if (!a.hijoDer().esVacio() && !a.hijoIz.esVacio()) {
				if (iz + 2 <= der) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		return false;
	}
}