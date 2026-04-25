#include "estadisticaJugador.h"
#include <iostream>
using namespace std;
//constructor
EstadisticaJugador::EstadisticaJugador() {
    partidosJugados = 0;
    goles = 0;
    minutosJugados = 0;
    asistencias = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
}
//constructor de copia
EstadisticaJugador::EstadisticaJugador(const EstadisticaJugador &copia) {
    partidosJugados = copia.partidosJugados;
    goles = copia.goles;
    minutosJugados = copia.minutosJugados;
    asistencias = copia.asistencias;
    tarjetasAmarillas = copia.tarjetasAmarillas;
    tarjetasRojas = copia.tarjetasRojas;
    faltas = copia.faltas;
}
//destructor
EstadisticaJugador::~EstadisticaJugador() {}

//getters
int EstadisticaJugador::getPartidosJugados() const {
    return partidosJugados;
}
int EstadisticaJugador::getGoles() const {
    return goles;
}
int EstadisticaJugador::getMinutosJugados() const {
    return minutosJugados;
}
int EstadisticaJugador::getAsistencias() const {
    return asistencias;
}
int EstadisticaJugador::getTarjetasAmarillas() const {    return tarjetasAmarillas;
}
int EstadisticaJugador::getTarjetasRojas() const {
    return tarjetasRojas;
}
int EstadisticaJugador::getFaltas() const {
    return faltas;
}
//Setters
void EstadisticaJugador::setPartidosJugados(int pj) { partidosJugados = pj;
}
void EstadisticaJugador::setGoles(int g) {
    goles = g;
}
void EstadisticaJugador::setMinutosJugados(int mj) { minutosJugados = mj;
}
void EstadisticaJugador::setAsistencias(int a) {
    asistencias = a;
}
void EstadisticaJugador::setTarjetasAmarillas(int ta) {
    tarjetasAmarillas = ta;
}
void EstadisticaJugador::setTarjetasRojas(int tr) { tarjetasRojas = tr; }
void EstadisticaJugador::setFaltas(int f) {
    faltas = f;
}
//actualiza las estadisticas segun lo que haya hecho el jugador en el partido
void EstadisticaJugador::actualizar(int goles, int minutos, int amarillas,
                                    int rojas, int faltas) {
    this->goles += goles;
    minutosJugados += minutos;
    tarjetasAmarillas += amarillas;
    tarjetasRojas += rojas;
    this->faltas += faltas;
}
void EstadisticaJugador::sumarPartido() {
    partidosJugados++;
}
//Despliegue
void EstadisticaJugador::mostrar() {
    cout << "Goles: " << goles << " Minutos: " << minutosJugados << endl;
}
//operador de sobrecarga
EstadisticaJugador &EstadisticaJugador::operator=(const EstadisticaJugador &otro) {
    if (this != &otro) {
        partidosJugados = otro.partidosJugados;
        goles = otro.goles;
        minutosJugados = otro.minutosJugados;
        asistencias = otro.asistencias;
        tarjetasAmarillas = otro.tarjetasAmarillas;
        tarjetasRojas = otro.tarjetasRojas;
        faltas = otro.faltas;
    }
    return *this;
}
