#include "estadisticaJugador.h"
#include <iostream>
using namespace std;

EstadisticaJugador::EstadisticaJugador() {
    partidosJugados = 0;
    goles = 0;
    minutosJugados = 0;
    asistencias = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
}

EstadisticaJugador::EstadisticaJugador(const EstadisticaJugador &copia) {
    partidosJugados = copia.partidosJugados;
    goles = copia.goles;
    minutosJugados = copia.minutosJugados;
    asistencias = copia.asistencias;
    tarjetasAmarillas = copia.tarjetasAmarillas;
    tarjetasRojas = copia.tarjetasRojas;
    faltas = copia.faltas;
}

EstadisticaJugador::~EstadisticaJugador() {}

int EstadisticaJugador::getPartidosJugados() { return partidosJugados; }
int EstadisticaJugador::getGoles() { return goles; }
int EstadisticaJugador::getMinutosJugados() { return minutosJugados; }
int EstadisticaJugador::getAsistencias() { return asistencias; }
int EstadisticaJugador::getTarjetasAmarillas() { return tarjetasAmarillas; }
int EstadisticaJugador::getTarjetasRojas() { return tarjetasRojas; }
int EstadisticaJugador::getFaltas() { return faltas; }

void EstadisticaJugador::setPartidosJugados(int pj) { partidosJugados = pj; }
void EstadisticaJugador::setGoles(int g) { goles = g; }
void EstadisticaJugador::setMinutosJugados(int mj) { minutosJugados = mj; }
void EstadisticaJugador::setAsistencias(int a) { asistencias = a; }
void EstadisticaJugador::setTarjetasAmarillas(int ta) {
    tarjetasAmarillas = ta;
}
void EstadisticaJugador::setTarjetasRojas(int tr) { tarjetasRojas = tr; }
void EstadisticaJugador::setFaltas(int f) { faltas = f; }

void EstadisticaJugador::actualizar(int goles, int minutos, int amarillas,
                                    int rojas, int faltas) {
    this->goles += goles;
    minutosJugados += minutos;
    tarjetasAmarillas += amarillas;
    tarjetasRojas += rojas;
    this->faltas += faltas;
}
void EstadisticaJugador::sumarPartido() { partidosJugados++; }
void EstadisticaJugador::mostrar() {
    cout << "Goles: " << goles << " Minutos: " << minutosJugados << endl;
}

EstadisticaJugador &
EstadisticaJugador::operator=(const EstadisticaJugador &otro) {
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
