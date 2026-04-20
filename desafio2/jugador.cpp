#include "jugador.h"
#include "estadisticajugador.h"
#include <iostream>
using namespace std;

//constructor
Jugador::Jugador(){
    nombre = "";
    apellido = "";
    numero = 0;
    estadisticas = EstadisticaJugador();
}

//constructor copia
Jugador::Jugador(const Jugador& copia){
    nombre = copia.nombre;
    apellido = copia.apellido;
    numero = copia.numero;
    estadisticas = copia.estadisticas;
}

//destructor
Jugador::~Jugador(){}

//getters
string Jugador::getNombre(){
    return nombre;
}

string Jugador::getApellido(){
    return apellido;
}

int Jugador::getNumero(){
    return numero;
}

int Jugador::getGoles(){
    return estadisticas.getGoles();
}

//setters
void Jugador::setNombre(const string nombre){
    this->nombre = nombre;
}

void Jugador::setApellido(const string apellido){
    this->apellido = apellido;
}

void Jugador::setNumero(int numero){
    this->numero = numero;
}

void Jugador::actualizarEstadisticas(int goles, int minutos, int amarillas, int rojas, int faltas){
    estadisticas.actualizar(goles, amarillas, rojas, faltas, minutos);
}

void Jugador::mostrarJugador(){
    cout << "Nombre: " << nombre << " " << apellido << endl;
    cout << "Numero: " << numero << endl;
    estadisticas.mostrar();
}

Jugador& Jugador::operator=(const Jugador& otro){
    if(this != &otro){
        nombre = otro.nombre;
        apellido = otro.apellido;
        numero = otro.numero;
        estadisticas = otro.estadisticas;
    }
    return *this;
}
