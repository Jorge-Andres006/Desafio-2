#include "grupo.h"
#include "cargarArchivos.h"
#include "equipo.h"
#include "partido.h"
#include <iostream>
//constructor
Grupo::Grupo() {
    letra = 'A';
    equipos = nullptr;
    cantidadEquipos = 0;
    partidos = nullptr;
    cantidadPartidos = 0;
}
//constructor de copia
Grupo::Grupo(const Grupo &copia) {
    letra = copia.letra;
    cantidadEquipos = copia.cantidadEquipos;
    cantidadPartidos = copia.cantidadPartidos;

    if (cantidadEquipos > 0) {
        equipos = new Equipo *[cantidadEquipos];
        memoria += sizeof(Equipo*) * cantidadEquipos;
        for (int i = 0; i < cantidadEquipos; i++){
            iteraciones++;
            equipos[i] = copia.equipos[i];
    }
    } else {
        equipos = nullptr;
    }

    if (cantidadPartidos > 0) {
        partidos = new Partido[cantidadPartidos];
        memoria += sizeof(Partido) * cantidadPartidos;
        for (int i = 0; i < cantidadPartidos; i++){
            iteraciones++;
            partidos[i] = copia.partidos[i];
        }

        } else {
        partidos = nullptr;
    }
}
//destructor
Grupo::~Grupo() {
    delete[] equipos;
    delete[] partidos;
}
//getters
char Grupo::getLetra() const {
    return letra;
}
int Grupo::getCantidadEquipos() const {
    return cantidadEquipos;
}
int Grupo::getCantidadPartidos() const {
    return cantidadPartidos;
}
Equipo **Grupo::getEquipos() const {
    return equipos;
}
Partido *Grupo::getPartidos() const {
    return partidos;
}
//Setters
void Grupo::setLetra(char l) {
    letra = l;
}
//agrega un equipo al grupo aumentando el arreglo dinamico
void Grupo::agregarEquipo(Equipo *equipo) {
    Equipo **nuevo = new Equipo *[cantidadEquipos + 1];
    memoria += sizeof(Equipo*) * (cantidadEquipos + 1);
    for (int i = 0; i < cantidadEquipos; i++){
        nuevo[i] = equipos[i];
        iteraciones++;
    }
    nuevo[cantidadEquipos] = equipo;
    delete[] equipos;
    equipos = nuevo;
    cantidadEquipos++;
}
//genera todos los partidos del grupo (todos contra todos)
void Grupo::generarPartidos() {
    if (cantidadEquipos != 4)
        return;

    delete[] partidos;
    cantidadPartidos = 6;
    partidos = new Partido[cantidadPartidos];
    memoria += sizeof(Partido) * cantidadPartidos;
    int cruces[6][2] = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};
    string arbitros[3] = {"codArbitro1", "codArbitro2", "codArbitro3"};

    for (int i = 0; i < 6; i++) {
        iteraciones++;
        partidos[i].setEquipos(equipos[cruces[i][0]], equipos[cruces[i][1]]);
        partidos[i].setHora("00:00");
        partidos[i].setSede("nombreSede");
        partidos[i].setArbitros(arbitros);
    }
}
//despliegue
void Grupo::mostrarGrupo() {
    cout << "----------------------\n";
    cout << "Grupo " << letra << "\n";
    cout << "----------------------\n";
    for (int i = 0; i < cantidadEquipos; i++) {
        iteraciones++;
        cout << equipos[i]->getPais() << " - "
             << equipos[i]->getConfederacion() << "\n";
    }
}
//operador de sobrecarga
Grupo &Grupo::operator=(const Grupo &otro) {
    if (this != &otro) {
        letra = otro.letra;

        delete[] equipos;
        delete[] partidos;

        cantidadEquipos = otro.cantidadEquipos;
        cantidadPartidos = otro.cantidadPartidos;

        if (cantidadEquipos > 0) {
            equipos = new Equipo *[cantidadEquipos];
            memoria += sizeof(Equipo*) * cantidadEquipos;
            for (int i = 0; i < cantidadEquipos; i++){
                iteraciones++;
                equipos[i] = otro.equipos[i];
            }
        } else {
            equipos = nullptr;
        }

        if (cantidadPartidos > 0) {
            partidos = new Partido[cantidadPartidos];
            memoria += sizeof(Partido) * cantidadPartidos;
            for (int i = 0; i < cantidadPartidos; i++){
                iteraciones++;
                partidos[i] = otro.partidos[i];
            }
        } else {
            partidos = nullptr;
        }
    }
    return *this;
}
