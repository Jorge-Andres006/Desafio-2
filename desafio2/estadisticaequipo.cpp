#include "estadisticaEquipo.h"
#include <iostream>
using namespace std;

EstadisticaEquipo::EstadisticaEquipo() {
    golesFavor = 0;
    golesContra = 0;
    partidosGanados = 0;
    partidosEmpatados = 0;
    partidosPerdidos = 0;
    minutosJugados = 0;
}

EstadisticaEquipo::EstadisticaEquipo(const EstadisticaEquipo &copia) {
    golesFavor = copia.golesFavor;
    golesContra = copia.golesContra;
    partidosGanados = copia.partidosGanados;
    partidosEmpatados = copia.partidosEmpatados;
    partidosPerdidos = copia.partidosPerdidos;
    minutosJugados = copia.minutosJugados;
}

EstadisticaEquipo::~EstadisticaEquipo() {}

int EstadisticaEquipo::getGolesFavor()  { return golesFavor; }
int EstadisticaEquipo::getGolesContra() { return golesContra; }
int EstadisticaEquipo::getPartidosGanados() { return partidosGanados; }
int EstadisticaEquipo::getPartidosEmpatados() { return partidosEmpatados; }
int EstadisticaEquipo::getPartidosPerdidos() { return partidosPerdidos; }

void EstadisticaEquipo::setGolesFavor(int gf) { golesFavor = gf; }
void EstadisticaEquipo::setGolesContra(int gc) { golesContra = gc; }
void EstadisticaEquipo::setPartidosGanados(int pg) { partidosGanados = pg; }
void EstadisticaEquipo::setPartidosEmpatados(int pe) { partidosEmpatados = pe; }
void EstadisticaEquipo::setPartidosPerdidos(int pp) { partidosPerdidos = pp; }

void EstadisticaEquipo::actualizar(int gf, int gc, int resultado) {
    golesFavor += gf;
    golesContra += gc;

    if (resultado == 1) {
        partidosGanados++;
    } else if (resultado == 0) {
        partidosEmpatados++;
    } else if (resultado == -1) {
        partidosPerdidos++;
    }
}

void EstadisticaEquipo::sumarMinutosJugados(int minutos) {
    minutosJugados += minutos;
}

void EstadisticaEquipo::mostrar() {
    cout << "Goles a favor: " << golesFavor << " Goles en contra: " << golesContra
         << endl;
    cout << "Partidos ganados: " << partidosGanados
         << " Partidos empatados: " << partidosEmpatados
         << " Partidos perdidos: " << partidosPerdidos << endl;
}

EstadisticaEquipo &EstadisticaEquipo::operator=(const EstadisticaEquipo &otro) {
    if (this != &otro) {
        golesFavor = otro.golesFavor;
        golesContra = otro.golesContra;
        partidosGanados = otro.partidosGanados;
        partidosEmpatados = otro.partidosEmpatados;
        partidosPerdidos = otro.partidosPerdidos;
        minutosJugados = otro.minutosJugados;
    }
    return *this;
}
