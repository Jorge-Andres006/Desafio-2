#include "jugador.h"
#include "estadisticajugador.h"
#include <iostream>
using namespace std;
//constructor
Jugador::Jugador() {
    nombre = "";
    apellido = "";
    numero = 0;
    estadisticas = EstadisticaJugador();
}
//constructor de copia
Jugador::Jugador(const Jugador &copia) {
    nombre = copia.nombre;
    apellido = copia.apellido;
    numero = copia.numero;
    estadisticas = copia.estadisticas;
}
//destructor
Jugador::~Jugador() {}

//getters
string Jugador::getNombre() const {
    return nombre;
}
string Jugador::getApellido() const {
    return apellido;
}
int Jugador::getNumero() const {
    return numero;
}
int Jugador::getGoles() const {
    return estadisticas.getGoles();
}
int Jugador::getMinutos() const {
    return estadisticas.getMinutosJugados();
}
int Jugador::getAmarillas() const {
    return estadisticas.getTarjetasAmarillas();
}
int Jugador::getRojas() const {
    return estadisticas.getTarjetasRojas();
}
int Jugador::getFaltas() const { return estadisticas.getFaltas(); }
int Jugador::getAsistencias() const {
    return estadisticas.getAsistencias();
}
int Jugador::getPartidos() const {
    return estadisticas.getPartidosJugados();
}
EstadisticaJugador &Jugador::getEstadistica()   {
    return estadisticas;
}
// setters
void Jugador::setNombre(const string nombre) { this->nombre = nombre; }
void Jugador::setApellido(const string apellido) { this->apellido = apellido; }
void Jugador::setNumero(int numero) { this->numero = numero; }
void Jugador::sumarPartido() { estadisticas.sumarPartido(); }
void Jugador::actualizarEstadisticas(int goles, int minutos, int amarillas,
                                     int rojas, int faltas) {
    estadisticas.actualizar(goles, minutos, amarillas, rojas, faltas);
}
//despliegue
void Jugador::mostrarJugador() {
    cout << "Nombre: " << nombre << " " << apellido << endl;
    cout << "Numero: " << numero << endl;
    estadisticas.mostrar();
}
//operador de sobrecarrga
Jugador &Jugador::operator=(const Jugador &otro) {
    if (this != &otro) {
        nombre = otro.nombre;
        apellido = otro.apellido;
        numero = otro.numero;
        estadisticas = otro.estadisticas;
    }
    return *this;
}
