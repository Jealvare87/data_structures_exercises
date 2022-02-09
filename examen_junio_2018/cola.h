/**
  @file Cola.h

  Implementaci�n del TAD Cola utilizando una
  lista enlazada de nodos.

  Estructura de Datos y Algoritmos
  Facultad de Inform�tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G�mez Mart�n, 2012   Mercedes G�mez Albarr�n, 2016
*/
#ifndef __COLA_LISTA_ENLAZADA_H
#define __COLA_LISTA_ENLAZADA_H
#include <cstddef>

/// Excepciones generadas por algunos m�todos
class EColaVacia {};
class EPosicionInexistente{};

/**
 Implementaci�n del TAD Cola utilizando una lista enlazada.

 Las operaciones son:

 - ColaVacia: -> Cola. Generadora implementada en el
   constructor sin par�metros.
 - pon: Cola, Elem -> Cola. Generadora
 - quita: Cola - -> Cola. Modificadora parcial.
 - primero: Cola - -> Elem. Observadora parcial.
 - esVacia: Cola -> Bool. Observadora.

 @author Marco Antonio G�mez Mart�n   Mercedes G�mez Albarr�n
 */
template <class T>
class Cola {
public:

	/** Constructor; operacion ColaVacia */
	Cola() : _prim(NULL), _ult(NULL) {
	}

	
	/**
	 A�ade un elemento en la parte trasera de la cola.
	 Operaci�n generadora.

	 @param elem Elemento a a�adir.
	*/
	void pon(const T &elem) {
		Nodo *nuevo = new Nodo(elem);
		if (esVacia()) _prim = nuevo; 
		else _ult->_sig = nuevo;
		_ult = nuevo;
	}

	/**
	 Elimina el primer elemento de la cola.
	 Operaci�n modificadora parcial.

	 error: falla si la cola est� vac�a
	*/
	void quita() {
		if (esVacia())
			throw EColaVacia();
		Nodo *aBorrar = _prim;
		if (_prim == _ult) 
			_prim = _ult = NULL;
		else
			_prim = _prim->_sig;
		delete aBorrar;
	}

	/**
	 Devuelve el primer elemento de la cola. Operaci�n
	 observadora parcial.
	 
	 error: falla si la cola est� vac�a
	 @return El primer elemento de la cola.
	 */
	const T &primero() const {
		if (esVacia())
			throw EColaVacia();
		return _prim->_elem;
	}

	/**
	 Indica si la cola tiene elementos o no.

	 @return true si la cola no tiene ning�n elemento.
	 */
	bool esVacia() const {
		return _prim == NULL;
	}


	/** Destructor; elimina la lista enlazada. */
	~Cola() {
		libera();
		_prim = _ult = NULL;
	}


	/** Constructor copia */
	Cola(const Cola<T> &other) : _prim(NULL), _ult(NULL) {
		copia(other);
	}

	/** Operador de asignaci�n */
	Cola<T> &operator=(const Cola<T> &other) {
		if (this != &other) { 
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. */
	bool operator==(const Cola<T> &rhs) const {
		Nodo *p1 = _prim;
		Nodo *p2 = rhs._prim;
		while ((p1 != NULL) && (p2 != NULL) && (p1->_elem == p2->_elem)) {
			p1 = p1->_sig;
			p2 = p2->_sig;
		}
		return (p1 == NULL) && (p2 == NULL);
	}

	bool operator!=(const Cola<T> &rhs) const {
		return !(*this == rhs);
	}

	/*Copia de cola ordenada*/

	void copiaCola(Cola<T> a) {
		Nodo * ant = nullptr;
		Nodo * actual = this->_prim;
		while (actual != NULL && a._prim != NULL) { // Si tiene siguiente y 
			if (a._prim->elem < actual->elem) {
				if (ant != nullptr) ant->_sig = a._prim; // Si tiene anterior lo introduzco entre medias
					a._prim->_sig = actual;
					a._prim = a->_sig;
			}
			ant = actual;
			actual = actual->_sig;
		}
		if (ant == nullptr) this->_prim = a._prim; // Lo que quede de cola se a�ade aqu�
		else {
			ant->_sig = a._prim;
		}
		a._prim = nullptr; // Vacias la cola
	}

	/**/
	/*
	*	COMPLEJIDAD
	*	Complejidad en el mejor de los casos es O(1)
	*	En el peor es O(n) porque recorres toda la cola sin encontrarlo
	*	siendo esta n el tama�o de la cola. => O(n)
	*/
	void llevarAlPrincipio(unsigned int pos) {
		Nodo* primero = this->_prim;
		Nodo* ant = nullptr;
		Nodo* actual = this->_prim;
		int i = 0;
		while (i < pos && actual != NULL) {
			ant = actual;
			actual = actual->_sig;
			++i;
		}
		if (actual == nullptr) throw EPosicionInexistente();
		ant->_sig = actual->_sig;
		actual->_sig = primero;
		this->_prim = actual; // A lo mejor es rizar el rizo (Preguntar a Herme)
	}
	
	/**/
	void desplaza(unsigned int pos, unsigned int dist) {
		Nodo* ant = nullptr;
		Nodo* actual = this->_prim;
		int i = 0;
		//Encuentra el nodo
		while (i < pos && actual != NULL) {
			ant = actual;
			actual = actual->_sig;
			++i;
		}
		i = 0;
		
		//Mover el nodo
		int fin = pos - dist;
		if (actual == NULL) {/*Excepcion*/}
		if (fin <= 0) { // Poniendo al principio si es demasiado grande
			ant->sig = actual->sig;
			actual->sig = this->_prim;
			this->_prim = actual;
		}
		else {
			Nodo* fin_nod = this->_prim;
			Nodo* ant_fin = nullptr;
			while (i < fin) {
				ant_fin = fin_nod;
				fin_nod = fin_nod->_sig;
				++i;
			}
			//swap
			ant->_sig = actual->_sig;
			ant_fin->_sig = actual;
			actual->_sig = fin_nod;
		}
	}

private:

	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y un puntero al nodo siguiente, que podr�a ser NULL si
	 el nodo es el �ltimo de la lista enlazada.
	 */
	class Nodo {
	public:
		Nodo() : _sig(NULL) {}
		Nodo(const T &elem) : _elem(elem), _sig(NULL) {}
		Nodo(const T &elem, Nodo *sig) : 
		    _elem(elem), _sig(sig) {}

		T _elem;
		Nodo *_sig;
	};


	/**
	Genera una copia de other en la cola receptora
	*/
	void copia(const Cola &other) {
		if (other.esVacia())
			_prim = _ult = NULL;
		else {
			Nodo *puntAOrigen = other._prim; 
			Nodo *ultimo; 
			_prim = new Nodo(puntAOrigen->_elem); 
			ultimo = _prim; 
			while (puntAOrigen->_sig != NULL) { 
				puntAOrigen = puntAOrigen->_sig; 
				ultimo->_sig = new Nodo(puntAOrigen->_elem); 
				ultimo = ultimo->_sig; 
			}
			_ult = ultimo;
		}
	}

	
	/**
	 Elimina todos los nodos de la lista enlazada que soporta la cola.
	 */
	void libera() {
		while (_prim != NULL) {
			Nodo *aBorrar = _prim;
			_prim = _prim->_sig;
			delete aBorrar;
		}
	}

	
	/** Puntero al primer elemento. */
	Nodo *_prim;

	/** Puntero al �ltimo elemento. */
	Nodo *_ult;
};

#endif // __PILA_LISTA_ENLAZADA_H