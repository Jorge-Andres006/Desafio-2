#include "tablagrupo.h"
#include "grupo.h"
#include "equipo.h"
#include <iostream>
using namespace std;

// constructor
TablaGrupo::TablaGrupo(Grupo& grupo){
    cantidad = grupo.getCantidadEquipos();

    equipos = new Equipo*[cantidad];
    puntos = new int[cantidad];

    for(int i = 0; i < cantidad; i++){
        equipos[i] = grupo.getEquipos()[i];
        puntos[i] = 0;
    }
}

// constructor copia
TablaGrupo::TablaGrupo(const TablaGrupo& copia){
    cantidad = copia.cantidad;

    equipos = new Equipo*[cantidad];
    puntos = new int[cantidad];

    for(int i = 0; i < cantidad; i++){
        equipos[i] = copia.equipos[i];
        puntos[i] = copia.puntos[i];
    }
}

// destructor
TablaGrupo::~TablaGrupo(){
    delete[] equipos;
    delete[] puntos;
}

// getters
int TablaGrupo::getCantidad(){
    return cantidad;
}

int TablaGrupo::getPuntos(int i){
    return puntos[i];
}

Equipo* TablaGrupo::getEquipo(int i){
    return equipos[i];
}


void TablaGrupo::calcularPuntos(){
    for(int i = 0; i < cantidad; i++){
        puntos[i] = 0;
    }
}


// void TablaGrupo::ordenarTabla(){
//     for(int i = 0; i < cantidad - 1; i++){
//         for(int j = 0; j < cantidad - 1 - i; j++){
//             if(puntos[j] < puntos[j+1]){
//                 int tempP = puntos[j];
//                 puntos[j] = puntos[j+1];
//                 puntos[j+1] = tempP;

//                 Equipo* tempE = equipos[j];
//                 equipos[j] = equipos[j+1];
//                 equipos[j+1] = tempE;
//             }
//         }
//     }
// } buscar algo mas eficiente que burbuja

// mostrar
void TablaGrupo::mostrarTabla(){
    for(int i = 0; i < cantidad; i++){
        cout << equipos[i]->getPais() << " - " << puntos[i] << endl;
    }
}

// primeros dos
Equipo* TablaGrupo::getPrimero(){
    if(cantidad > 0) return equipos[0];
    return nullptr;
}

Equipo* TablaGrupo::getSegundo(){
    if(cantidad > 1) return equipos[1];
    return nullptr;
}

// operador =
TablaGrupo& TablaGrupo::operator=(const TablaGrupo& otro){
    if(this != &otro){
        delete[] equipos;
        delete[] puntos;

        cantidad = otro.cantidad;

        equipos = new Equipo*[cantidad];
        puntos = new int[cantidad];

        for(int i = 0; i < cantidad; i++){
            equipos[i] = otro.equipos[i];
            puntos[i] = otro.puntos[i];
        }
    }

    return *this;
}
