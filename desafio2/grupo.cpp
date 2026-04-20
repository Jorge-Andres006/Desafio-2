#include "grupo.h"
#include "equipo.h"
#include <iostream>
Grupo::Grupo(){
    letra = 'A';
    equipos = nullptr;
    cantidadEquipos = 0;
}

Grupo::Grupo(const Grupo& copia){
    letra = copia.letra;

    cantidadEquipos = copia.cantidadEquipos;

    if(cantidadEquipos > 0){
        equipos = new Equipo*[cantidadEquipos];
        for(int i = 0; i < cantidadEquipos; i++){
            equipos[i] = copia.equipos[i];
        }
    } else {
        equipos = nullptr;
    }
}

Grupo::~Grupo(){
    delete[] equipos;
}

char Grupo::getLetra(){
    return letra;
}

int Grupo::getCantidadEquipos(){
    return cantidadEquipos;
}

Equipo** Grupo::getEquipos(){
    return equipos;
}

void Grupo::setLetra(char letra){
    this->letra = letra;
}

void Grupo::agregarEquipo(Equipo* equipo){
    Equipo** nuevo = new Equipo*[cantidadEquipos + 1];

    for(int i = 0; i < cantidadEquipos; i++){
        nuevo[i] = equipos[i];
    }

    nuevo[cantidadEquipos] = equipo;

    delete[] equipos;
    equipos = nuevo;
    cantidadEquipos++;
}

void Grupo::mostrarGrupo(){

    cout << "----------------------" << endl;
    cout << "Grupo " << letra << endl;
    cout << "----------------------" << endl;

    for(int i = 0; i < cantidadEquipos; i++){
        cout << equipos[i]->getPais()
        << " - "
        << equipos[i]->getConfederacion()
        << endl;
    }

    cout << endl;
}

Grupo& Grupo::operator=(const Grupo& otro){
    if(this != &otro){
        letra = otro.letra;

        delete[] equipos;

        cantidadEquipos = otro.cantidadEquipos;

        if(cantidadEquipos > 0){
            equipos = new Equipo*[cantidadEquipos];
            for(int i = 0; i < cantidadEquipos; i++){
                equipos[i] = otro.equipos[i];
            }
        } else {
            equipos = nullptr;
        }
    }

    return *this;
}
