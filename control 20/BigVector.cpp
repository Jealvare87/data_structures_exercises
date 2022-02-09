#include "BigVector.h"
     
	 
BigVector::BigVector() { // A IMPLEMENTAR 
	this->vect = DiccionarioHash<unsigned long, double>();
}

double BigVector::valorDe(const unsigned long i) const {
	  // A IMPLEMENTAR
	if (this->vect.contiene(i)) {
		return this->vect.valorPara(i);
	}
	return NULL;
}  

void BigVector::ponValor(unsigned long i, double v) {
	// A IMPLEMENTAR
	this->vect.inserta(i, v);
}  

double BigVector::productoEscalar(const BigVector& v) const {
	// A IMPLEMENTAR
	double result = 0;
	DiccionarioHash<unsigned long, double>::ConstIterator it = vect.cbegin();
	while (it != vect.cend()) {
		double aux = v.valorDe(it.clave());
		if (aux != NULL) {
			result += it.valor() * aux;
		}
		it.next();
	}

	return result;
}
   
