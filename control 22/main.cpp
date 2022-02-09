#include "GestionAdmisiones.h"

#include <iostream>
#include <string>
using namespace std;

/**
Este programa lee y ejecuta una serie de acciones a realizar sobre un
sistema de gestión de admisiones.
Las posibles órdenes son las siguientes:
- admite codigo nombre edad sintomas G: Admite un paciente con codigo
  'codigo', nombre 'nombre', edad 'edad', sintomas 'sintomas' y nivel de
  gravedad G (NORMAL, LEVE, GRAVE). Tanto 'nombre' como 'sintomas' no
  deben contener espacios en blanco. Como respuesta imprime OK si el codigo no está
  duplicado, o CODIGO_PACIENTE_DUPLICADO en otro caso.
- atiende: Simula la atención de un paciente (obtiene la información del siguiente
  paciente a atender, y lo elimina del sistema). Como respuesta imprime OK, o
  NO_HAY_PACIENTES en caso de que en el sistema no haya pacientes.
- siguiente: Muestra toda la información del siguiente paciente a atender.
  Como respuesta muestra una linea del tipo
        codigo nombre edad sintomas G (con G el nivel de gravedad)
  o bien NO_HAY_PACIENTES en caso de que en el sistema no haya pacientes.		
- datos c: Visualiza los datos (nombre, edad y síntomas) del paciente con codigo 'c'. 	
- desiste c: Elimina el paciente con codigo 'c' del sistema (si es que existe). Siempre
  imprime OK como respuesta.
- en_espera: Imprime SI si hay pacientes en espera, y NO en otro caso.

Ejemplo de entrada:

admite 1 jose 22 dolor_muelas LEVE
admite 2 pepe 25 dolor_barriga LEVE
siguiente
admite 2 juan 23 dolor_cabeza NORMAL
admite 3 juan 23 dolor_cabeza NORMAL
siguiente
atiende
datos 3
datos 4
datos 1
siguiente
atiende
siguiente
atiende
siguiente
atiende

Salida producida:

OK
OK
1 jose 22 dolor_muelas LEVE
CODIGO_PACIENTE_DUPLICADO
OK
3 juan 23 dolor_cabeza NORMAL
OK
PACIENTE_NO_EXISTE
PACIENTE_NO_EXISTE
jose 22 dolor_muelas
1 jose 22 dolor_muelas LEVE
OK
2 pepe 25 dolor_barriga LEVE
OK
NO_HAY_PACIENTES
NO_HAY_PACIENTES
*/


Gravedad gravedad_paciente(string gravedad) {
	if (gravedad == "LEVE") return LEVE;
	else if (gravedad == "NORMAL") return NORMAL;
	else return GRAVE;
}

void admite(GestionAdmisiones& admisiones) {
	CodigoPaciente codigo;
	string nombre;
	unsigned int edad;
	string sintomas;
	string gravedad;
	cin >> codigo >> nombre >> edad >> sintomas >> gravedad;
	try {
		admisiones.an_paciente(codigo, nombre, edad, sintomas, gravedad_paciente(gravedad));
		cout << "OK" << endl;
	}
	catch (EPacienteDuplicado) {
		cout << "CODIGO_PACIENTE_DUPLICADO" << endl;
	}
}

void atiende(GestionAdmisiones& admisiones) {
	try {
		CodigoPaciente codigo_siguiente;
		Gravedad gravedad_siguiente;
		admisiones.siguiente(codigo_siguiente, gravedad_siguiente);
		admisiones.elimina(codigo_siguiente);
		cout << "OK" << endl;
	}
	catch (ENoHayPacientes) {
		cout << "NO_HAY_PACIENTES" << endl;
	}
}

void desiste(GestionAdmisiones& admisiones) {
	CodigoPaciente codigo;
	cin >> codigo;
	admisiones.elimina(codigo);
	cout << "OK" << endl;
}

void muestra_siguiente(GestionAdmisiones& admisiones) {
	CodigoPaciente codigo;
	Gravedad gravedad;
	string nombre;
	unsigned int edad;
	string sintomas;
	try {
		admisiones.siguiente(codigo, gravedad);
		admisiones.info_paciente(codigo, nombre, edad, sintomas);
		cout << codigo << " " << nombre << " " << edad << " " << sintomas << " ";
		switch (gravedad) {
		case LEVE: cout << "LEVE"; break;
		case NORMAL: cout << "NORMAL"; break;
		case GRAVE: cout << "GRAVE"; break;
		}
		cout << endl;
	}
	catch (ENoHayPacientes) {
		cout << "NO_HAY_PACIENTES" << endl;
	}
}

void datos_paciente(GestionAdmisiones& admisiones) {
	CodigoPaciente codigo;
	string nombre;
	unsigned int edad;
	string sintomas;
	cin >> codigo;
	try {
		admisiones.info_paciente(codigo, nombre,edad, sintomas);
		cout << nombre << " " << edad << " " << sintomas << endl;
	}
	catch (EPacienteNoExiste) {
		cout << "PACIENTE_NO_EXISTE" << endl;
	}
}

void en_espera(const GestionAdmisiones& admisiones) {
	if (admisiones.hay_pacientes()) 
		cout << "SI" << endl;
	else  
		cout << "NO" << endl;
}


int main() {
	GestionAdmisiones admisiones;
	string comando;
	while(cin >> comando) {
			if (comando == "admite") admite(admisiones);
			else if (comando == "atiende") atiende(admisiones);
			else if (comando == "desiste") desiste(admisiones);
			else if (comando == "siguiente") muestra_siguiente(admisiones);
			else if (comando == "datos") datos_paciente(admisiones);
			else if (comando == "en_espera") en_espera(admisiones);
	}
	return 0;
}