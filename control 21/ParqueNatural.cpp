#include "ParqueNatural.h"


ParqueNatural::ParqueNatural() {
	this->registro_ecosistema = DiccionarioHash<string, DiccionarioHash<string, int>>();
	this->registro_ecosistema_especie = DiccionarioHash<string, Lista<string>>();
	this->registro_total_por_especie = Diccionario<string, int>();
}

void ParqueNatural::an_ecosistema(const string& ecosistema) {
	if (this->registro_ecosistema.contiene(ecosistema)) throw EEcosistemaDuplicado();
	else {
		this->registro_ecosistema.inserta(ecosistema, DiccionarioHash<string, int>());
		this->registro_ecosistema_especie.inserta(ecosistema, Lista<string>());
	}
}

void ParqueNatural::an_ejemplares(const string& ecosistema, const string& especie, int n) {
	DiccionarioHash<string, DiccionarioHash<string, int>>::Iterator it = this->registro_ecosistema.busca(ecosistema);
	if(it == this->registro_ecosistema.end()) throw EEcosistemaNoExiste();
	else {
		if (it.valor().contiene(especie)) {
			it.valor().inserta(especie, it.valor().valorPara(especie) + n);
		}
		else {
			it.valor().inserta(especie, n);
			(this->registro_ecosistema_especie.busca(ecosistema)).valor().pon_ppio(especie);
		}
		Diccionario<string, int>::Iterator it2 = this->registro_total_por_especie.busca(especie);
		if (it2 == this->registro_total_por_especie.end()) {
			this->registro_total_por_especie.inserta(especie, n);
		}
		else {
			it2.setVal(it2.valor() + n);
		}
	}
}

Lista<string> ParqueNatural::lista_especies_ecosistema(const string& ecosistema, int n) const {
	if (!this->registro_ecosistema_especie.contiene(ecosistema)) throw EEcosistemaNoExiste();
	Lista<string>::ConstIterator it = this->registro_ecosistema_especie.valorPara(ecosistema).cbegin();
	Lista<string> ret = Lista<string>();
	int i = 0;
	while (i < n && it != this->registro_ecosistema_especie.valorPara(ecosistema).cend()) {
		ret.pon_final(it.elem());
		i++;
		it.next();
	}
	return ret;
}

int ParqueNatural::numero_ejemplares_en_ecosistema(const string& ecosistema, const string& especie) const {
	if (!this->registro_ecosistema.contiene(ecosistema)) throw EEcosistemaNoExiste();
	else {
		if (!this->registro_ecosistema.valorPara(ecosistema).contiene(especie)) {
			return 0;
		}
		else {
			return this->registro_ecosistema.valorPara(ecosistema).valorPara(especie);
		}
	}
}

Lista<string> ParqueNatural::lista_especies_parque() const {
	Lista<string> ret = Lista<string>();
	Diccionario<string, int>::ConstIterator it = this->registro_total_por_especie.cbegin();
	while (it != this->registro_total_por_especie.cend()) {
		ret.pon_final(it.clave());
		it.next();
	}
	return ret;
}

int ParqueNatural::numero_ejemplares_en_parque(const string& especie) const {
	Diccionario<string, int>::ConstIterator it = this->registro_total_por_especie.cbusca(especie);
	if (it == this->registro_total_por_especie.cend()) return 0;
	return it.valor();
}
 