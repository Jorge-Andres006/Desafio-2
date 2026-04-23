#include "eliminatoria.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Eliminatoria::Eliminatoria(){
    partidos = nullptr;
    cantidad = 0;
}

Eliminatoria::Eliminatoria(const Eliminatoria& otra){

    cantidad = otra.cantidad;

    if(cantidad > 0){
        partidos = new Partido[cantidad];
        for(int i = 0; i < cantidad; i++){
            partidos[i] = otra.partidos[i];
        }
    }else{
        partidos = nullptr;
    }
}

Eliminatoria::~Eliminatoria(){
    delete[] partidos;
}

Eliminatoria& Eliminatoria::operator=(const Eliminatoria& otra){

    if(this != &otra){

        delete[] partidos;

        cantidad = otra.cantidad;

        if(cantidad > 0){
            partidos = new Partido[cantidad];
            for(int i = 0; i < cantidad; i++){
                partidos[i] = otra.partidos[i];
            }
        }else{
            partidos = nullptr;
        }
    }

    return *this;
}

int Eliminatoria::getCantidad(){
    return cantidad;
}

Partido* Eliminatoria::getPartidos(){
    return partidos;
}

void Eliminatoria::agregarPartido(Equipo* e1, Equipo* e2){

    Partido* nuevo = new Partido[cantidad + 1];

    for(int i = 0; i < cantidad; i++){
        nuevo[i] = partidos[i];
    }

    nuevo[cantidad].setEquipos(e1, e2);
    nuevo[cantidad].setHora("00:00");
    nuevo[cantidad].setSede("nombreSede");

    string arbitros[3] = {"codArbitro1","codArbitro2","codArbitro3"};
    nuevo[cantidad].setArbitros(arbitros);

    delete[] partidos;
    partidos = nuevo;
    cantidad++;
}

void Eliminatoria::crearDesdeClasificados(
    Equipo** equiposPrimeros,
    Equipo** equiposSegundos,
    Equipo** mejoresTerceros,
    char* grupoPrimeros,
    char* grupoSegundos,
    char* grupoMejoresTerceros
    ){

    bool usado[8] = {false};

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 8; j++){

            if(!usado[j] && grupoMejoresTerceros[j] != grupoPrimeros[i]){
                agregarPartido(equiposPrimeros[i], mejoresTerceros[j]);
                usado[j] = true;
                break;
            }
        }
    }

    for(int i = 8; i < 12; i++){
        agregarPartido(equiposPrimeros[i], equiposSegundos[i]);
    }

    for(int i = 0; i < 8; i += 2){
        agregarPartido(equiposSegundos[i], equiposSegundos[i+1]);
    }
}

Equipo* Eliminatoria::simularPartidoEliminatoria(Partido& partido){

    partido.setFecha("2026-07-10");

    partido.simularPartido();

    int goles1 = partido.getGolesEquipo1();
    int goles2 = partido.getGolesEquipo2();

    if(goles1 > goles2){
        return partido.getEquipo1();
    }

    if(goles2 > goles1){
        return partido.getEquipo2();
    }

    return resolverEmpate(partido);
}

Equipo* Eliminatoria::resolverEmpate(Partido& partido){

    Equipo* equipo1 = partido.getEquipo1();
    Equipo* equipo2 = partido.getEquipo2();

    int ranking1 = equipo1->getRanking();
    int ranking2 = equipo2->getRanking();

    int total = ranking1 + ranking2;
    int aleatorio = rand() % total;

    if(aleatorio < ranking2){
        return equipo1;
    }else{
        return equipo2;
    }
}

Equipo** Eliminatoria::simularRonda(int& cantidadGanadores, const string& nombreRonda){

    cout << "\n====== " << nombreRonda << " ======\n";

    cantidadGanadores = cantidad;

    Equipo** ganadores = new Equipo*[cantidadGanadores];

    for(int i = 0; i < cantidad; i++){

        ganadores[i] = simularPartidoEliminatoria(partidos[i]);

        partidos[i].mostrarPartido();

        cout << endl;
    }

    return ganadores;
}

Eliminatoria Eliminatoria::crearSiguienteRonda(Equipo** equipos, int cantidadEquipos){

    Eliminatoria nueva;

    for(int i = 0; i < cantidadEquipos - 1; i += 2){
        nueva.agregarPartido(equipos[i], equipos[i+1]);
    }

    return nueva;
}

void Eliminatoria::mostrar(){

    cout << "\n===== DIECISEISAVOS =====\n";

    for(int i = 0; i < cantidad; i++){
        cout << partidos[i].getEquipo1()->getPais()
        << " vs "
        << partidos[i].getEquipo2()->getPais()
        << endl;
    }
}
