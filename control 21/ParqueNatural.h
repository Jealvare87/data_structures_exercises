#ifndef _PARQUE_NATURAL_H
#define _PARQUE_NATURAL_H

#include "diccionario.h"
#include "lista.h"
#include "DiccionarioHash.h"
#include <string>
using namespace std;


/*
 Excepciones levantadas por las operaciones
*/
class EEcosistemaDuplicado {};

class EEcosistemaNoExiste {};



class ParqueNatural {
public:
   ParqueNatural();
   void an_ecosistema(const string& ecosistema);
   void an_ejemplares(const string& ecosistema, const string& especie, int n);
   Lista<string> lista_especies_ecosistema(const string& ecosistema, int n) const;
   int numero_ejemplares_en_ecosistema(const string& ecosistema, const string& especie) const;
   Lista<string> lista_especies_parque() const;
   int numero_ejemplares_en_parque(const string& especie) const;
   
private:
  
	Diccionario<string, int> registro_total_por_especie; //Aquí guardamos el registro de especies global.
	DiccionarioHash<string, DiccionarioHash<string, int>> registro_ecosistema; //Aquí guardamos el registro de las especies de cada ecosistema.
	DiccionarioHash<string, Lista<string>> registro_ecosistema_especie; //Aquí guardamos las esècies que hay en cada ecosistema.
};
 
#endif