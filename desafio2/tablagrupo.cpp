#include "tablagrupo.h"
#include "equipo.h"
#include "grupo.h"
#include "partido.h"
#include <iostream>
using namespace std;

TablaGrupo::TablaGrupo(Grupo &grupo) {
    this->grupo = &grupo;
    cantidad = grupo.getCantidadEquipos();

    equipos = new Equipo *[cantidad];
    puntos = new int[cantidad];
    partidosJugados = new int[cantidad];
    partidosGanados = new int[cantidad];
    partidosEmpatados = new int[cantidad];
    partidosPerdidos = new int[cantidad];
    diferenciaGol = new int[cantidad];

    for (int i = 0; i < cantidad; i++) {
        equipos[i] = grupo.getEquipos()[i];
        puntos[i] = 0;
        partidosJugados[i] = 0;
        partidosGanados[i] = 0;
        partidosEmpatados[i] = 0;
        partidosPerdidos[i] = 0;
        diferenciaGol[i] = 0;
    }
}

TablaGrupo::TablaGrupo(const TablaGrupo &copia) {
    grupo = copia.grupo;
    cantidad = copia.cantidad;

    equipos = new Equipo *[cantidad];
    puntos = new int[cantidad];
    partidosJugados = new int[cantidad];
    partidosGanados = new int[cantidad];
    partidosEmpatados = new int[cantidad];
    partidosPerdidos = new int[cantidad];
    diferenciaGol = new int[cantidad];

    for (int i = 0; i < cantidad; i++) {
        equipos[i] = copia.equipos[i];
        puntos[i] = copia.puntos[i];
        partidosJugados[i] = copia.partidosJugados[i];
        partidosGanados[i] = copia.partidosGanados[i];
        partidosEmpatados[i] = copia.partidosEmpatados[i];
        partidosPerdidos[i] = copia.partidosPerdidos[i];
        diferenciaGol[i] = copia.diferenciaGol[i];
    }
}

TablaGrupo::~TablaGrupo() {
    delete[] equipos;
    delete[] puntos;
    delete[] partidosJugados;
    delete[] partidosGanados;
    delete[] partidosEmpatados;
    delete[] partidosPerdidos;
    delete[] diferenciaGol;
}

int TablaGrupo::getCantidad() { return cantidad; }
int TablaGrupo::getPuntos(int i) { return puntos[i]; }
int TablaGrupo::getDiferenciaGol(int i) { return diferenciaGol[i]; }
Equipo *TablaGrupo::getEquipo(int i) { return equipos[i]; }

void TablaGrupo::calcularPuntos() {

    for (int i = 0; i < cantidad; i++) {
        puntos[i] = partidosJugados[i] = partidosGanados[i] = 0;
        partidosEmpatados[i] = partidosPerdidos[i] = diferenciaGol[i] = 0;
    }

    Partido *partidos = grupo->getPartidos();
    int cant = grupo->getCantidadPartidos();

    for (int i = 0; i < cant; i++) {
        Equipo *e1 = partidos[i].getEquipo1();
        Equipo *e2 = partidos[i].getEquipo2();
        int g1 = partidos[i].getGolesEquipo1();
        int g2 = partidos[i].getGolesEquipo2();

        int idx1 = -1, idx2 = -1;
        for (int j = 0; j < cantidad; j++) {
            if (equipos[j] == e1)
                idx1 = j;
            if (equipos[j] == e2)
                idx2 = j;
        }
        if (idx1 == -1 || idx2 == -1)
            continue;

        partidosJugados[idx1]++;
        partidosJugados[idx2]++;
        diferenciaGol[idx1] += (g1 - g2);
        diferenciaGol[idx2] += (g2 - g1);

        if (g1 > g2) {
            puntos[idx1] += 3;
            partidosGanados[idx1]++;
            partidosPerdidos[idx2]++;
        } else if (g2 > g1) {
            puntos[idx2] += 3;
            partidosGanados[idx2]++;
            partidosPerdidos[idx1]++;
        } else {
            puntos[idx1]++;
            puntos[idx2]++;
            partidosEmpatados[idx1]++;
            partidosEmpatados[idx2]++;
        }
    }
}

void TablaGrupo::ordenarTabla() {
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - 1 - i; j++) {

            bool cambiar = (puntos[j] < puntos[j + 1]) ||
                           (puntos[j] == puntos[j + 1] &&
                                                           diferenciaGol[j] < diferenciaGol[j + 1]);

            if (cambiar) {

#define SWAP_INT(a, b)                                                         \
                {                                                                            \
                int t = (a);                                                               \
                (a) = (b);                                                                 \
                (b) = t;                                                                   \
            }
                SWAP_INT(puntos[j], puntos[j + 1]);
                SWAP_INT(partidosJugados[j], partidosJugados[j + 1]);
                SWAP_INT(partidosGanados[j], partidosGanados[j + 1]);
                SWAP_INT(partidosEmpatados[j], partidosEmpatados[j + 1]);
                SWAP_INT(partidosPerdidos[j], partidosPerdidos[j + 1]);
                SWAP_INT(diferenciaGol[j], diferenciaGol[j + 1]);
#undef SWAP_INT

                Equipo *tempE = equipos[j];
                equipos[j] = equipos[j + 1];
                equipos[j + 1] = tempE;
            }
        }
    }
}

void TablaGrupo::mostrarTabla() {
    cout << "Equipo          PJ   PG   PE   PP   DG   PTS\n";
    for (int i = 0; i < cantidad; i++) {
        string nombre = equipos[i]->getPais();
        if (nombre.length() > 15)
            nombre = nombre.substr(0, 15);
        cout << nombre;
        for (int s = nombre.length(); s < 15; s++)
            cout << " ";
        cout << partidosJugados[i] << "    " << partidosGanados[i] << "    "
             << partidosEmpatados[i] << "    " << partidosPerdidos[i] << "    ";
        if (diferenciaGol[i] >= 0)
            cout << " ";
        cout << diferenciaGol[i] << "   " << puntos[i] << "\n";
    }
}

Equipo *TablaGrupo::getPrimero() {
    return (cantidad > 0) ? equipos[0] : nullptr;
}
Equipo *TablaGrupo::getSegundo() {
    return (cantidad > 1) ? equipos[1] : nullptr;
}

TablaGrupo &TablaGrupo::operator=(const TablaGrupo &otro) {
    if (this != &otro) {
        delete[] equipos;
        delete[] puntos;
        delete[] partidosJugados;
        delete[] partidosGanados;
        delete[] partidosEmpatados;
        delete[] partidosPerdidos;
        delete[] diferenciaGol;

        grupo = otro.grupo;
        cantidad = otro.cantidad;

        equipos = new Equipo *[cantidad];
        puntos = new int[cantidad];
        partidosJugados = new int[cantidad];
        partidosGanados = new int[cantidad];
        partidosEmpatados = new int[cantidad];
        partidosPerdidos = new int[cantidad];
        diferenciaGol = new int[cantidad];

        for (int i = 0; i < cantidad; i++) {
            equipos[i] = otro.equipos[i];
            puntos[i] = otro.puntos[i];
            partidosJugados[i] = otro.partidosJugados[i];
            partidosGanados[i] = otro.partidosGanados[i];
            partidosEmpatados[i] = otro.partidosEmpatados[i];
            partidosPerdidos[i] = otro.partidosPerdidos[i];
            diferenciaGol[i] = otro.diferenciaGol[i];
        }
    }
    return *this;
}
