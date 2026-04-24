#include "grupo.h"
#include "equipo.h"
#include "partido.h"
#include <iostream>

Grupo::Grupo() {
    letra = 'A';
    equipos = nullptr;
    cantidadEquipos = 0;
    partidos = nullptr;
    cantidadPartidos = 0;
}

Grupo::Grupo(const Grupo &copia) {
    letra = copia.letra;
    cantidadEquipos = copia.cantidadEquipos;
    cantidadPartidos = copia.cantidadPartidos;

    if (cantidadEquipos > 0) {
        equipos = new Equipo *[cantidadEquipos];
        for (int i = 0; i < cantidadEquipos; i++)
            equipos[i] = copia.equipos[i];
    } else {
        equipos = nullptr;
    }

    if (cantidadPartidos > 0) {
        partidos = new Partido[cantidadPartidos];
        for (int i = 0; i < cantidadPartidos; i++)
            partidos[i] = copia.partidos[i];
    } else {
        partidos = nullptr;
    }
}

Grupo::~Grupo() {
    delete[] equipos;
    delete[] partidos;
}

char Grupo::getLetra() { return letra; }
int Grupo::getCantidadEquipos() { return cantidadEquipos; }
int Grupo::getCantidadPartidos() { return cantidadPartidos; }
Equipo **Grupo::getEquipos() { return equipos; }
Partido *Grupo::getPartidos() { return partidos; }

void Grupo::setLetra(char l) { letra = l; }

void Grupo::agregarEquipo(Equipo *equipo) {
    Equipo **nuevo = new Equipo *[cantidadEquipos + 1];
    for (int i = 0; i < cantidadEquipos; i++)
        nuevo[i] = equipos[i];
    nuevo[cantidadEquipos] = equipo;
    delete[] equipos;
    equipos = nuevo;
    cantidadEquipos++;
}

void Grupo::generarPartidos() {
    if (cantidadEquipos != 4)
        return;

    delete[] partidos;
    cantidadPartidos = 6;
    partidos = new Partido[cantidadPartidos];

    int cruces[6][2] = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};
    string arbitros[3] = {"codArbitro1", "codArbitro2", "codArbitro3"};

    for (int i = 0; i < 6; i++) {
        partidos[i].setEquipos(equipos[cruces[i][0]], equipos[cruces[i][1]]);
        partidos[i].setHora("00:00");
        partidos[i].setSede("nombreSede");
        partidos[i].setArbitros(arbitros);
    }
}

void Grupo::mostrarGrupo() {
    cout << "----------------------\n";
    cout << "Grupo " << letra << "\n";
    cout << "----------------------\n";
    for (int i = 0; i < cantidadEquipos; i++)
        cout << equipos[i]->getPais() << " - " << equipos[i]->getConfederacion()
             << "\n";
    cout << "\n";
}

Grupo &Grupo::operator=(const Grupo &otro) {
    if (this != &otro) {
        letra = otro.letra;

        delete[] equipos;
        delete[] partidos;

        cantidadEquipos = otro.cantidadEquipos;
        cantidadPartidos = otro.cantidadPartidos;

        if (cantidadEquipos > 0) {
            equipos = new Equipo *[cantidadEquipos];
            for (int i = 0; i < cantidadEquipos; i++)
                equipos[i] = otro.equipos[i];
        } else {
            equipos = nullptr;
        }

        if (cantidadPartidos > 0) {
            partidos = new Partido[cantidadPartidos];
            for (int i = 0; i < cantidadPartidos; i++)
                partidos[i] = otro.partidos[i];
        } else {
            partidos = nullptr;
        }
    }
    return *this;
}
