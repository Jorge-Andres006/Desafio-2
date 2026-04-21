#include "equipo.h"
#include "jugador.h"
#include <iostream>
using namespace std;

Equipo::Equipo(){
    pais="";
    confederacion="";
    federacion="";
    directorTecnico="";
    ranking=0;
    estadisticas = EstadisticaEquipo();
    jugadores=nullptr;
    cantidadJugadores=0;
}

Equipo::Equipo(const Equipo& copia){
    pais=copia.pais;
    confederacion=copia.confederacion;
    federacion=copia.federacion;
    directorTecnico=copia.directorTecnico;
    ranking=copia.ranking;
    estadisticas = copia.estadisticas;

    cantidadJugadores=copia.cantidadJugadores;

    if(cantidadJugadores>0){
        jugadores=new Jugador[cantidadJugadores];
        for(int i=0;i<cantidadJugadores;i++){
            jugadores[i]=copia.jugadores[i];
        }
    } else {
        jugadores=nullptr;
    }
}

Equipo::~Equipo(){
    delete[] jugadores;
}

//getters
string Equipo::getPais(){ return pais; }
int Equipo::getRanking(){ return ranking; }
string Equipo::getDirectorTecnico(){ return directorTecnico; }
string Equipo::getConfederacion(){ return confederacion; }

Jugador* Equipo::getJugador(int indice){
    if(indice>=0 && indice<cantidadJugadores){
        return &jugadores[indice];
    }
    return nullptr;
}

int Equipo::getCantidadJugadores(){
    return cantidadJugadores;
}

//setters
void Equipo::setPais(const string& pais){ this->pais=pais; }
void Equipo::setConfederacion(const string& confederacion){ this->confederacion=confederacion; }
void Equipo::setDirectorTecnico(const string& dt){ this->directorTecnico=dt; }
void Equipo::setRanking(int ranking){ this->ranking=ranking; }
void Equipo::setFederacion(const string& federacion){ this->federacion=federacion; }

//metodos
void Equipo::agregarJugador(const Jugador& jugador){
    Jugador* nuevo=new Jugador[cantidadJugadores+1];

    for(int i=0;i<cantidadJugadores;i++){
        nuevo[i]=jugadores[i];
    }

    nuevo[cantidadJugadores]=jugador;

    delete[] jugadores;
    jugadores=nuevo;
    cantidadJugadores++;
}

void Equipo::actualizarEstadisticas(int golesFavor,int golesContra,int resultado){
    estadisticas.actualizar(golesFavor,golesContra,resultado);
}

void Equipo::cargarEstadisticas(int golesFavor,int golesContra,int partidosGanados,int partidosEmpatados,int partidosPerdidos){
    estadisticas.setGolesFavor(golesFavor);
    estadisticas.setGolesContra(golesContra);
    estadisticas.setPartidosGanados(partidosGanados);
    estadisticas.setPartidosEmpatados(partidosEmpatados);
    estadisticas.setPartidosPerdidos(partidosPerdidos);
}

void Equipo::mostrarEquipo(){
    cout << "Direccion en memoria: " << this << endl;
    cout << "Pais: " << pais << endl;
    cout << "Ranking: " << ranking << endl;
    cout << "Confederacion: " << confederacion << endl;
    cout << "Director Tecnico: " << directorTecnico << endl;
    estadisticas.mostrar();
}

Equipo& Equipo::operator=(const Equipo& otro){
    if(this != &otro){
        pais = otro.pais;
        confederacion = otro.confederacion;
        federacion = otro.federacion;
        directorTecnico = otro.directorTecnico;
        ranking = otro.ranking;
        estadisticas = otro.estadisticas;

        delete[] jugadores;

        cantidadJugadores = otro.cantidadJugadores;

        if(cantidadJugadores > 0){
            jugadores = new Jugador[cantidadJugadores];
            for(int i = 0; i < cantidadJugadores; i++){
                jugadores[i] = otro.jugadores[i];
            }
        } else {
            jugadores = nullptr;
        }
    }

    return *this;
}
