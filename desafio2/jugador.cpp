#include "Jugador.h"
#include <iostream>
using namespace std;

//constructor
Jugador::Jugador(){
    nombre = "";
    apellido = "";
    numero = 0;
    goles = 0;
}

//constructor copia
Jugador::Jugador(const Jugador& copia){
    nombre = copia.nombre;
    apellido = copia.apellido;
    numero = copia.numero;
    goles = copia.goles;
}

//destructor
Jugador::~Jugador(){

}

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
    return goles;
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

//estadísticas
void Jugador::actualizarEstadisticas(int goles, int minutos, int amarillas, int rojas, int faltas){
    this->goles = this->goles + goles;
}

//mostrar
void Jugador::mostrarJugador(){
    cout << "Nombre: " << nombre << " " << apellido << endl;
    cout << "Numero: " << numero << endl;
    cout << "Goles: " << goles << endl;
}

Jugador& Jugador::operator=(const Jugador& otro){
    if(this != &otro){
        nombre = otro.nombre;
        apellido = otro.apellido;
        numero = otro.numero;
        goles = otro.goles;
    }
    return *this;
}
