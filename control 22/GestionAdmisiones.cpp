#include "GestionAdmisiones.h"

GestionAdmisiones::GestionAdmisiones() {

}


void GestionAdmisiones::an_paciente(CodigoPaciente codigo, const string& nombre, unsigned int edad, const string& sintomas, Gravedad gravedad) {

	if (_pacientes.contiene(codigo)) throw EPacienteDuplicado();
	else {
		if (gravedad == GRAVE) {
			_grave.pon_ppio(codigo);
			Paciente p = Paciente(nombre, edad, sintomas, gravedad); //Creado el paciente
			_pacientes.inserta(codigo, p);
		}
		else if (gravedad == NORMAL) {
			_normal.pon_ppio(codigo);
			Paciente p = Paciente(nombre, edad, sintomas, gravedad); //Creado el paciente
			_pacientes.inserta(codigo, p);
		}
		else{
			_leve.pon_ppio(codigo);
			Paciente p = Paciente(nombre, edad, sintomas, gravedad); //Creado el paciente
			_pacientes.inserta(codigo, p);
		}
	}
}

void GestionAdmisiones::info_paciente(CodigoPaciente codigo, string& nombre, unsigned int& edad, string& sintomas) const {

	DiccionarioHash<CodigoPaciente, Paciente>::ConstIterator it = _pacientes.cbusca(codigo);
	if (it == _pacientes.cend()) throw EPacienteNoExiste();
	else {
		//Paciente p = _pacientes.valorPara(codigo);
		Paciente p = it.valor();
		nombre = p._nombre;
		edad = p._edad;
		sintomas = p._descrip;
	}
}

void GestionAdmisiones::siguiente(CodigoPaciente& codigo, Gravedad& gravedad) const {

	if (hay_pacientes()) {
		if (!_grave.esVacia()) {
			codigo = _grave.ultimo();
			gravedad = GRAVE;
		}
		else if (!_normal.esVacia()) {
			codigo = _normal.ultimo();
			gravedad = NORMAL;
		}
		else if(! _leve.esVacia()){
			codigo = _leve.ultimo();
			gravedad = LEVE;
		}
	}
	else throw ENoHayPacientes();
}

bool GestionAdmisiones::hay_pacientes() const {  
	return !_grave.esVacia() || !_normal.esVacia() || !_leve.esVacia();
}

void GestionAdmisiones::elimina(CodigoPaciente codigo) {
	DiccionarioHash<CodigoPaciente, Paciente>::Iterator it = _pacientes.busca(codigo);
	if (it != _pacientes.end()) { //Si existe
		Lista<CodigoPaciente>::Iterator it2 = _grave.begin();
		Gravedad gravd = it.valor()._gravedad;
		if (gravd == NORMAL) {
			it2 = _normal.begin();
		}
		else if (gravd == LEVE) {
			it2 = _leve.begin();
		}
		while (it2.elem() != codigo) {
			it2.next();
		}
		switch (gravd) {
			case GRAVE:
				_grave.eliminar(it2);
				break;
			case NORMAL:
				_normal.eliminar(it2);
				break;
			case LEVE:
				_leve.eliminar(it2);
				break;
		}
		_pacientes.borra(codigo);
	}
}
   
