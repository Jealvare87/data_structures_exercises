#ifndef _GESTION_ADMISIONES_H
#define _GESTION_ADMISIONES_H

#include <string>
#include "DiccionarioHash.h"
#include "lista.h"
using namespace std;


/** 
Tipo que representa el código de los
pacientes
*/
typedef unsigned int CodigoPaciente;

typedef Lista<CodigoPaciente>::Iterator tIterador;


/** 
Tipo que representa el grado de gravedad de un
paciente.
*/
typedef enum{LEVE,NORMAL,GRAVE} Gravedad;

/**
Excepción que debe levantarse cuando trata de darse de alta
un paciente con un código duplicado
*/
class EPacienteDuplicado {};

/**
Excepción que debe levantarse cuando trata de consultarse los
datos de un paciente a través de un código que no existe.
*/
class EPacienteNoExiste {};

/**
Excepción que debe levantarse cuando trata de consultarse la información
del siguiente paciente a atender, pero no hay pacientes en el sistema.
*/
class ENoHayPacientes {};

/**
Clase que implementa el TAD
*/
class GestionAdmisiones {
public:
   /**
     Constructora: crea un sistema de gestión de admisiones vacío
   */
   GestionAdmisiones();
   /**
     Añade un paciente al sistema. 
	 Levanta la excepción EPacienteDuplicado si ya hay un paciente esperando con el
	 mismo codigo
	 @param codigo El código del paciente
	 @param nombre El nombre del paciente
	 @param edad La edad del paciente
	 @param sintomas Los sintomas del paciente
	 @param gravedad El nivel de gravedad del paciente
   */
   void an_paciente(CodigoPaciente codigo, const string& nombre, unsigned int edad, const string& sintomas, Gravedad gravedad);
   /**
     Recupera los datos de un paciente, dado su código. 
	 Levanta la excepción EPacienteNoExiste si el código no se corresponde con el
	 de ningún paciente en espera
	 @param codigo El código del paciente
	 @param nombre El nombre del paciente
	 @param edad La edad del paciente
	 @param sintomas Los sintomas del paciente
   */   
   void info_paciente(CodigoPaciente codigo, string& nombre, unsigned int& edad, string& sintomas) const;
   /**
     Recupera el código y el nivel de gravedad del siguiente paciente que va a ser atendido.
	 Levanta la excepción ENoHayPacientes en caso de que no haya pacientes en espera.
	 @param codigo El código del paciente
	 @param gravedad El nivel de gravedad del paciente
   */   
   void siguiente(CodigoPaciente& codigo, Gravedad& gravedad) const;
   /**
     Determina si hay pacientes en espera
	 @return true si hay pacientes, false en otro caso.
   */   
   bool hay_pacientes() const;
   /**
     Elimina del sistema todo el rasto de un paciente, dado su código.
	 Si el código no existe, la operación no tiene efecto.
	 @param codigo El codigo del paciente a eliminar. 
   */   
   void elimina(CodigoPaciente codigo);
private:
	class Paciente {
	public:
		Paciente(string nom, unsigned int ed, string d, Gravedad grav) :_nombre(nom), _edad(ed), _descrip(d), _gravedad(grav){}
		string _nombre;
		unsigned int _edad;
		string _descrip;
		Gravedad _gravedad;
	};
  // Debe elegirse la representación más adecuada para implementar
  // eficientemente este TAD
	Lista<CodigoPaciente> _grave;
	Lista<CodigoPaciente> _normal;
	Lista<CodigoPaciente> _leve;
	DiccionarioHash<CodigoPaciente, Paciente> _pacientes;
};

#endif