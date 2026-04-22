#include "tablagrupo.h"
#include "grupo.h"
#include "equipo.h"
#include "partido.h"
#include <iostream>
using namespace std;

// constructor
TablaGrupo::TablaGrupo(Grupo& grupo){
    this->grupo = &grupo;

    cantidad = grupo.getCantidadEquipos();

    equipos = new Equipo*[cantidad];
    puntos = new int[cantidad];
    partidosJugados = new int[cantidad];
    partidosGanados = new int[cantidad];
    partidosEmpatados = new int[cantidad];
    partidosPerdidos = new int[cantidad];
    diferenciaGol = new int[cantidad];

    for(int i = 0; i < cantidad; i++){
        equipos[i] = grupo.getEquipos()[i];

        puntos[i] = 0;
        partidosJugados[i] = 0;
        partidosGanados[i] = 0;
        partidosEmpatados[i] = 0;
        partidosPerdidos[i] = 0;
        diferenciaGol[i] = 0;
    }
}


// destructor
TablaGrupo::~TablaGrupo(){
    delete[] equipos;
    delete[] puntos;
    delete[] partidosJugados;
    delete[] partidosGanados;
    delete[] partidosEmpatados;
    delete[] partidosPerdidos;
    delete[] diferenciaGol;
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

    Partido* partidos = grupo->getPartidos();
    int cant = grupo->getCantidadPartidos();

    for(int i = 0; i < cantidad; i++){
        puntos[i] = 0;
        partidosJugados[i] = 0;
        partidosGanados[i] = 0;
        partidosEmpatados[i] = 0;
        partidosPerdidos[i] = 0;
        diferenciaGol[i] = 0;
    }

    for(int i = 0; i < cant; i++){

        Equipo* e1 = partidos[i].getEquipo1();
        Equipo* e2 = partidos[i].getEquipo2();

        int g1 = partidos[i].getGolesEquipo1();
        int g2 = partidos[i].getGolesEquipo2();

        int idx1 = -1, idx2 = -1;

        for(int j = 0; j < cantidad; j++){
            if(equipos[j] == e1) idx1 = j;
            if(equipos[j] == e2) idx2 = j;
        }

        if(idx1 == -1 || idx2 == -1) continue;

        partidosJugados[idx1]++;
        partidosJugados[idx2]++;

        diferenciaGol[idx1] += (g1 - g2);
        diferenciaGol[idx2] += (g2 - g1);

        if(g1 > g2){
            puntos[idx1] += 3;
            partidosGanados[idx1]++;
            partidosPerdidos[idx2]++;
        }
        else if(g2 > g1){
            puntos[idx2] += 3;
            partidosGanados[idx2]++;
            partidosPerdidos[idx1]++;
        }
        else{
            puntos[idx1] += 1;
            puntos[idx2] += 1;
            partidosEmpatados[idx1]++;
            partidosEmpatados[idx2]++;
        }
    }
}

void TablaGrupo::ordenarTabla(){
    for(int i = 0; i < cantidad - 1; i++){
        for(int j = 0; j < cantidad - 1 - i; j++){

            if(puntos[j] < puntos[j+1] ||
                (puntos[j] == puntos[j+1] && diferenciaGol[j] < diferenciaGol[j+1])){

                int tempP = puntos[j];
                puntos[j] = puntos[j+1];
                puntos[j+1] = tempP;

                Equipo* tempE = equipos[j];
                equipos[j] = equipos[j+1];
                equipos[j+1] = tempE;

                int tempPJ = partidosJugados[j];
                partidosJugados[j] = partidosJugados[j+1];
                partidosJugados[j+1] = tempPJ;

                int tempPG = partidosGanados[j];
                partidosGanados[j] = partidosGanados[j+1];
                partidosGanados[j+1] = tempPG;

                int tempPE = partidosEmpatados[j];
                partidosEmpatados[j] = partidosEmpatados[j+1];
                partidosEmpatados[j+1] = tempPE;

                int tempPP = partidosPerdidos[j];
                partidosPerdidos[j] = partidosPerdidos[j+1];
                partidosPerdidos[j+1] = tempPP;

                int tempDG = diferenciaGol[j];
                diferenciaGol[j] = diferenciaGol[j+1];
                diferenciaGol[j+1] = tempDG;
            }
        }
    }
}
void imprimirEspacios(int n){
    for(int i = 0; i < n; i++) cout << " ";
}
void TablaGrupo::mostrarTabla(){

    cout << "Equipo          PJ   PG   PE   PP   DG   PTS\n";

    for(int i = 0; i < cantidad; i++){

        string nombre = equipos[i]->getPais();

        if(nombre.length() > 15){
            nombre = nombre.substr(0, 15);
        }
        cout << nombre;
        imprimirEspacios(15 - nombre.length());

        cout << partidosJugados[i] << "    ";
        cout << partidosGanados[i] << "    ";
        cout << partidosEmpatados[i] << "    ";
        cout << partidosPerdidos[i] << "    ";

        if(diferenciaGol[i] >= 0) cout << " ";
        cout << diferenciaGol[i] << "   ";

        cout << puntos[i] << endl;
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
