#include "torneo.h"
#include "equipo.h"
#include "grupo.h"
#include "partido.h"
#include "tablagrupo.h"
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

void Torneo::realizarSorteo(){
    conformarBombos();
    while(!sorteo()){}
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
void Torneo::mostrarGrupos(){
    for(int i = 0; i < cantidadGrupos; i++){
        grupos[i].mostrarGrupo();
    }
}
void Torneo::asignarFechasGrupos(){

    int partidosPorDia[19] = {0};
    int ultimoDia[48];

    for(int i = 0; i < 48; i++) ultimoDia[i] = -10;

    for(int g = 0; g < cantidadGrupos; g++){

        Partido* partidos = grupos[g].getPartidos();
        int cantidad = grupos[g].getCantidadPartidos();

        for(int i = 0; i < cantidad; i++){

            Equipo* e1 = partidos[i].getEquipo1();
            Equipo* e2 = partidos[i].getEquipo2();

            int id1 = -1, id2 = -1;

            for(int k = 0; k < cantidadEquipos; k++){
                if(equipos[k] == e1) id1 = k;
                if(equipos[k] == e2) id2 = k;
            }

            bool asignado = false;

            for(int d = 0; d < 19; d++){

                if(partidosPorDia[d] >= 4) continue;
                if(d - ultimoDia[id1] < 3) continue;
                if(d - ultimoDia[id2] < 3) continue;

                int dia = 20 + d;

                string fecha;

                if(dia <= 30){
                    if(dia < 10) fecha = "2026-06-0" + to_string(dia);
                    else fecha = "2026-06-" + to_string(dia);
                }else{
                    int dj = dia - 30;
                    if(dj < 10) fecha = "2026-07-0" + to_string(dj);
                    else fecha = "2026-07-" + to_string(dj);
                }

                partidos[i].setFecha(fecha);

                partidosPorDia[d]++;
                ultimoDia[id1] = d;
                ultimoDia[id2] = d;

                asignado = true;
                break;
            }

            if(!asignado){

                for(int d = 0; d < 19; d++){

                    if(partidosPorDia[d] >= 4) continue;

                    int dia = 20 + d;

                    string fecha;

                    if(dia <= 30){
                        if(dia < 10) fecha = "2026-06-0" + to_string(dia);
                        else fecha = "2026-06-" + to_string(dia);
                    }else{
                        int dj = dia - 30;
                        if(dj < 10) fecha = "2026-07-0" + to_string(dj);
                        else fecha = "2026-07-" + to_string(dj);
                    }

                    partidos[i].setFecha(fecha);

                    partidosPorDia[d]++;
                    ultimoDia[id1] = d;
                    ultimoDia[id2] = d;

                    break;
                }
            }
        }
    }
}
void Torneo::mostrarTablasGrupos(){

    for(int i = 0; i < cantidadGrupos; i++){

        cout << "\n======================" << endl;
        cout << "GRUPO " << char('A' + i) << endl;
        cout << "======================" << endl;

        TablaGrupo tabla(grupos[i]);

        tabla.calcularPuntos();
        tabla.ordenarTabla();
        tabla.mostrarTabla();
    }
}
void Torneo::simularTorneo(){

    cout << "Inicio simulacion" << endl;

    for(int i = 0; i < cantidadGrupos; i++){
        grupos[i].generarPartidos();
    }

    asignarFechasGrupos();

    for(int g = 0; g < cantidadGrupos; g++){

        cout << "Partidos grupo " << grupos[g].getLetra() << endl;

        Partido* partidos = grupos[g].getPartidos();
        int cant = grupos[g].getCantidadPartidos();

        for(int i = 0; i < cant; i++){
            partidos[i].simularPartido();
            partidos[i].mostrarPartido();
        }
        cout<<endl;
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
