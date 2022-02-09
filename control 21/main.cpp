#include "ParqueNatural.h"

#include <iostream>
#include <string>
using namespace std;


void lista(const Lista<string>& l) {
	   Lista<string>::ConstIterator i = l.cbegin();
	   while (i != l.cend()) {
		   cout << i.elem() << " ";
		   i.next();
	   }	
	   cout << endl;
}

void an_ecosistema(ParqueNatural& parque) {
   string ecosistema;
   cin >> ecosistema;
   cout << "an_ecosistema " << ecosistema << " => ";
   try {
	   parque.an_ecosistema(ecosistema);
	   cout << "OK" << endl;
   }   
   catch(EEcosistemaDuplicado) {
	   cout << "ECOSISTEMA_DUPLICADO" << endl;
   }
   
}

void an_ejemplares(ParqueNatural& parque) {
   string ecosistema;
   cin >> ecosistema;
   string especie;
   cin >> especie;
   int n;
   cin >> n;
   cout << "an_ejemplares " << ecosistema << " " << especie << " " << n << " => ";
   try {
	   parque.an_ejemplares(ecosistema,especie,n);
	   cout << "OK" << endl;
   }   
   catch(EEcosistemaNoExiste) {
	   cout << "NO_EXISTE_ECOSISTEMA" << endl;
   }
   
}

void lista_especies_ecosistema(const ParqueNatural& parque) {
   string ecosistema;
   cin >> ecosistema;
   int n;
   cin >> n;
   cout << "lista_especies_ecosistema " << ecosistema << " " << n << " => ";
   try {
	   lista(parque.lista_especies_ecosistema(ecosistema,n));
   }   
   catch(EEcosistemaNoExiste) {
	   cout << "NO_EXISTE_ECOSISTEMA" << endl;
   } 
}

void numero_ejemplares_en_ecosistema(const ParqueNatural& parque) {
   string ecosistema;
   cin >> ecosistema;
   string especie;
   cin >> especie;
   cout << "numero_ejemplares_en_ecosistema " << ecosistema << " " << especie << " => ";
   try {
	   cout << parque.numero_ejemplares_en_ecosistema(ecosistema,especie) << endl;
   }   
   catch(EEcosistemaNoExiste) {
	   cout << "NO_EXISTE_ECOSISTEMA" << endl;
   } 
}

void lista_especies_parque(const ParqueNatural& parque) {
	cout << "lista_especies_parque => ";
	lista(parque.lista_especies_parque());
}

void numero_ejemplares_en_parque(const ParqueNatural& parque) {
   string especie;
   cin >> especie;
   cout << "numero_ejemplares_en_parque " << especie << " => " << 
	   parque.numero_ejemplares_en_parque(especie) << endl;
}


int main() {
	ParqueNatural parque;
	string comando;
	while(cin >> comando) {
			if (comando == "an_ecosistema") an_ecosistema(parque);
			else if (comando == "an_ejemplares") an_ejemplares(parque);
			else if (comando == "lista_especies_ecosistema") lista_especies_ecosistema(parque);
			else if (comando == "numero_ejemplares_en_ecosistema") numero_ejemplares_en_ecosistema(parque);
			else if (comando == "lista_especies_parque") lista_especies_parque(parque);
			else if (comando == "numero_ejemplares_en_parque") numero_ejemplares_en_parque(parque);
	}
	return 0;
}