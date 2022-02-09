#ifndef __BIGVECTOR_H
#define __BIGVECTOR_H

#include "DiccionarioHash.h"

class BigVector {
  public:
     /**
	   Crea un vector disperso en el que todos los elementos son 0
	   (operación "crea")
	 */
     BigVector();  

	 /**
	   Consulta el valor de un elemento del vector disperso
	   @param i El índice del elemento
	   @return El valor del elemento
	 */
	 double valorDe(const unsigned long i) const;

	 /**
	   Fija el valor de un elemento del vector disperso
	   @param i El índice del elemento
	   @param v El valor del elemento a actualizar
	 */
	 void ponValor(unsigned long i, double v);

	 /**
	   Encuenta el productor escalar del receptor y del argumento
	   @param v El vector con el que se quiere encontrar el producto escalar del
	            rector
	   @return El valor del producto escalar
	 */
	 double productoEscalar(const BigVector& v) const;
   private:
      // A COMPLETAR: Campos y operaciones auxiliares
	  // necesarios para soportar el TAD.
	   DiccionarioHash<unsigned long, double> vect;
};

#endif