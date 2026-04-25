#include "tablagrupo.h"
#include "equipo.h"
#include "grupo.h"
#include "partido.h"
#include <iostream>
using namespace std;
//constructor
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
        iteraciones++;
        equipos[i] = grupo.getEquipos()[i];
        puntos[i] = 0;
        partidosJugados[i] = 0;
        partidosGanados[i] = 0;
        partidosEmpatados[i] = 0;
        partidosPerdidos[i] = 0;
        diferenciaGol[i] = 0;
    }
    memoria += sizeof(Equipo*) * cantidad;
    memoria += sizeof(int) * cantidad * 6;
}
//constructor de copia
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
        iteraciones++;
        equipos[i] = copia.equipos[i];
        puntos[i] = copia.puntos[i];
        partidosJugados[i] = copia.partidosJugados[i];
        partidosGanados[i] = copia.partidosGanados[i];
        partidosEmpatados[i] = copia.partidosEmpatados[i];
        partidosPerdidos[i] = copia.partidosPerdidos[i];
        diferenciaGol[i] = copia.diferenciaGol[i];
    }
    memoria += sizeof(Equipo*) * cantidad;
    memoria += sizeof(int) * cantidad * 6;
}
//destructor
TablaGrupo::~TablaGrupo() {
    delete[] equipos;
    delete[] puntos;
    delete[] partidosJugados;
    delete[] partidosGanados;
    delete[] partidosEmpatados;
    delete[] partidosPerdidos;
    delete[] diferenciaGol;
}
//getters
int TablaGrupo::getCantidad() const  { return cantidad; }
int TablaGrupo::getPuntos(int i) const { return puntos[i]; }
int TablaGrupo::getDiferenciaGol(int i) const { return diferenciaGol[i]; }
Equipo *TablaGrupo::getEquipo(int i) const { return equipos[i]; }
Equipo *TablaGrupo::getPrimero() {
    return (cantidad > 0) ? equipos[0] : nullptr;
}
Equipo *TablaGrupo::getSegundo() {
    return (cantidad > 1) ? equipos[1] : nullptr;
}

//calcula los puntos obtenidos por cada equipo
void TablaGrupo::calcularPuntos() {

    for (int i = 0; i < cantidad; i++) {
        iteraciones++;
        puntos[i] = 0;
        partidosJugados[i] =0;
        partidosGanados[i] = 0;
        partidosEmpatados[i] = 0;
        partidosPerdidos[i] =0;
        diferenciaGol[i] = 0;
    }

    Partido *partidos = grupo->getPartidos();
    int cant = grupo->getCantidadPartidos();

    for (int i = 0; i < cant; i++) {
        iteraciones++;
        Equipo *e1 = partidos[i].getEquipo1();
        Equipo *e2 = partidos[i].getEquipo2();
        int g1 = partidos[i].getGolesEquipo1();
        int g2 = partidos[i].getGolesEquipo2();

        int idx1 = -1, idx2 = -1;
        for (int j = 0; j < cantidad; j++) {
            iteraciones++;
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
//usa insertion para ordenar la tabla
void TablaGrupo::ordenarTabla() {

    for (int i = 1; i < cantidad; i++) {
        iteraciones++;
        int p  = puntos[i];
        int pj = partidosJugados[i];
        int pg = partidosGanados[i];
        int pe = partidosEmpatados[i];
        int pp = partidosPerdidos[i];
        int dg = diferenciaGol[i];
        Equipo* e = equipos[i];
        int j = i - 1;
        while (j >= 0 &&
               (puntos[j] < p ||
                (puntos[j] == p && diferenciaGol[j] < dg))) {
            iteraciones++;
            puntos[j + 1] = puntos[j];
            partidosJugados[j + 1] = partidosJugados[j];
            partidosGanados[j + 1] = partidosGanados[j];
            partidosEmpatados[j + 1] = partidosEmpatados[j];
            partidosPerdidos[j + 1] = partidosPerdidos[j];
            diferenciaGol[j + 1] = diferenciaGol[j];
            equipos[j + 1] = equipos[j];

            j--;
        }
        puntos[j + 1] = p;
        partidosJugados[j + 1] = pj;
        partidosGanados[j + 1] = pg;
        partidosEmpatados[j + 1] = pe;
        partidosPerdidos[j + 1] = pp;
        diferenciaGol[j + 1] = dg;
        equipos[j + 1] = e;
    }
}
//muestra la tabla
void TablaGrupo::mostrarTabla() {
    cout << "Equipo         PJ   PG   PE   PP   DG   PTS\n";
    for (int i = 0; i < cantidad; i++) {
        iteraciones++;
        string nombre = equipos[i]->getPais();
        if (nombre.length() > 15)
            nombre = nombre.substr(0, 15);
        cout << nombre;
        for (int s = nombre.length(); s < 15; s++){
            iteraciones++;
            cout << " ";
        }
        cout << partidosJugados[i] << "    " << partidosGanados[i] << "    "
             << partidosEmpatados[i] << "    " << partidosPerdidos[i] << "    ";
        if (diferenciaGol[i] >= 0)
            cout << " ";
        cout << diferenciaGol[i] << "   " << puntos[i] << "\n";
    }
}

//operador de sobrecarga
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
            iteraciones++;
            equipos[i] = otro.equipos[i];
            puntos[i] = otro.puntos[i];
            partidosJugados[i] = otro.partidosJugados[i];
            partidosGanados[i] = otro.partidosGanados[i];
            partidosEmpatados[i] = otro.partidosEmpatados[i];
            partidosPerdidos[i] = otro.partidosPerdidos[i];
            diferenciaGol[i] = otro.diferenciaGol[i];
        }
    }
    memoria += sizeof(Equipo*) * cantidad;
    memoria += sizeof(int) * cantidad * 6;
    return *this;
}
