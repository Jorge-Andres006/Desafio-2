#include "torneo.h"
#include "equipo.h"
#include "grupo.h"
#include <iostream>
#include <random>

using namespace std;

int aleatorio(int limite){
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(0, limite - 1);
    return dist(gen);
}

//constructor
Torneo::Torneo(){
    equipos = NULL;
    cantidadEquipos = 0;

    grupos = NULL;
    cantidadGrupos = 0;

    bombo1 = bombo2 = bombo3 = bombo4 = NULL;
}

//destructor
Torneo::~Torneo(){
    delete[] bombo1;
    delete[] bombo2;
    delete[] bombo3;
    delete[] bombo4;
    delete[] grupos;
}

//set equipos
void Torneo::setEquipos(Equipo** equipos, int cantidad){
    this->equipos = equipos;
    this->cantidadEquipos = cantidad;
}


void Torneo::inicializarGrupos(int cantidad){
    cantidadGrupos = cantidad;
    grupos = new Grupo[cantidadGrupos];

    for(int i = 0; i < cantidadGrupos; i++){
        grupos[i].setLetra('A' + i);
    }
}

void Torneo::ordenarPorRanking(){
    for(int i = 0; i < cantidadEquipos - 1; i++){
        for(int j = 0; j < cantidadEquipos - i - 1; j++){

            if(equipos[j]->getRanking() > equipos[j+1]->getRanking()){
                Equipo* aux = equipos[j];
                equipos[j] = equipos[j+1];
                equipos[j+1] = aux;
            }
        }
    }
}
void Torneo::conformarBombos(){

    ordenarPorRanking();

    bombo1 = new Equipo*[12];
    bombo2 = new Equipo*[12];
    bombo3 = new Equipo*[12];
    bombo4 = new Equipo*[12];

    int i1 = 0, i2 = 0, i3 = 0, i4 = 0;


    for(int i = 0; i < cantidadEquipos; i++){
        if(equipos[i]->getPais() == "United States"){
            bombo1[i1++] = equipos[i];
            equipos[i] = NULL;
            break;
        }
    }


    for(int i = 0; i < cantidadEquipos; i++){

        if(equipos[i] == NULL) continue;

        if(i1 < 12) bombo1[i1++] = equipos[i];
        else if(i2 < 12) bombo2[i2++] = equipos[i];
        else if(i3 < 12) bombo3[i3++] = equipos[i];
        else bombo4[i4++] = equipos[i];
    }
}

//validar confederaciones
bool Torneo::esValido(Grupo& grupo, Equipo* nuevo){

    int contadorUEFA = 0;

    Equipo** lista = grupo.getEquipos();

    for(int i = 0; i < grupo.getCantidadEquipos(); i++){

        if(lista[i]->getConfederacion() == nuevo->getConfederacion()){

            if(nuevo->getConfederacion() == "UEFA"){
                contadorUEFA++;
                if(contadorUEFA >= 2) return false;
            }else{
                return false;
            }
        }
    }

    return true;
}

//sacar equipo de un bombo
int Torneo::sortearDeBombo(Equipo** bombo, bool* usado, int tamano, Grupo& grupo){

    int intentos = 0;

    while(intentos < 100){

        int idx = aleatorio(tamano);

        if(!usado[idx]){

            if(esValido(grupo, bombo[idx])){
                grupo.agregarEquipo(bombo[idx]);
                usado[idx] = true;
                return 1;
            }
        }

        intentos++;
    }

    return 0;
}


bool Torneo::sorteo(){

    bool usado1[12] = {false};
    bool usado2[12] = {false};
    bool usado3[12] = {false};
    bool usado4[12] = {false};

    for(int i = 0; i < cantidadGrupos; i++){
        grupos[i] = Grupo();
        grupos[i].setLetra('A' + i);
    }

    for(int i = 0; i < cantidadGrupos; i++){

        if(!sortearDeBombo(bombo1, usado1, 12, grupos[i])) return false;
        if(!sortearDeBombo(bombo2, usado2, 12, grupos[i])) return false;
        if(!sortearDeBombo(bombo3, usado3, 12, grupos[i])) return false;
        if(!sortearDeBombo(bombo4, usado4, 12, grupos[i])) return false;
    }

    return true;
}
void Torneo::simularTorneo(){

    conformarBombos();

    while(!sorteo()){

    }

    cout << "Sorteo completado!" << endl;
}


void Torneo::mostrarGrupos(){
    for(int i = 0; i < cantidadGrupos; i++){
        grupos[i].mostrarGrupo();
    }
}
void Torneo::mostrarBombos(){
    // cout << "====== Bombo 1 ======" << endl;
    // for(int i = 0; i < 12; i++){
    //     cout << bombo1[i]->getPais()
    //     << " - "
    //     << bombo1[i]->getConfederacion()
    //     << endl;
    // }

    // cout << endl;

    // cout << "====== Bombo 2 ======" << endl;
    // for(int i = 0; i < 12; i++){
    //     cout << bombo2[i]->getPais()
    //     << " - "
    //     << bombo2[i]->getConfederacion()
    //     << endl;
    // }

    // cout << endl;

    // cout << "====== Bombo 3 ======" << endl;
    // for(int i = 0; i < 12; i++){
    //     cout << bombo3[i]->getPais()
    //     << " - "
    //     << bombo3[i]->getConfederacion()
    //     << endl;
    // }

    // cout << endl;

    // cout << "====== Bombo 4 ======" << endl;
    // for(int i = 0; i < 12; i++){
    //     cout << bombo4[i]->getPais()
    //     << " - "
    //     << bombo4[i]->getConfederacion()
    //     << endl;
    // }

    // cout << endl;
}
