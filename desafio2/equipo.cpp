#include "Equipo.h"
#include "Jugador.h"
#include <iostream>
using namespace std;

//constructor
Equipo::Equipo(){
    pais="";
    confederacion="";
    federacion="";
    directorTecnico="";

    ranking=0;
    puntos=0;
    golesFavor=0;
    golesContra=0;
    partidosGanados=0;
    partidosEmpatados=0;
    partidosPerdidos=0;
    tarjetasAmarillas=0;
    tarjetasRojas=0;
    faltas=0;

    jugadores=nullptr;
    cantidadJugadores=0;
}

//constructor copia
Equipo::Equipo(const Equipo& copia){
    pais=copia.pais;
    confederacion=copia.confederacion;
    federacion=copia.federacion;
    directorTecnico=copia.directorTecnico;

    ranking=copia.ranking;
    puntos=copia.puntos;

    golesFavor=copia.golesFavor;
    golesContra=copia.golesContra;
    partidosGanados=copia.partidosGanados;
    partidosEmpatados=copia.partidosEmpatados;
    partidosPerdidos=copia.partidosPerdidos;
    tarjetasAmarillas=copia.tarjetasAmarillas;
    tarjetasRojas=copia.tarjetasRojas;
    faltas=copia.faltas;

    cantidadJugadores=copia.cantidadJugadores;

    if(cantidadJugadores>0){
        jugadores=new Jugador[cantidadJugadores];
        for(int i=0;i<cantidadJugadores;i++){
            jugadores[i] = copia.jugadores[i];
        }
    }
    else{
        jugadores=nullptr;
    }
}

//destructor
Equipo::~Equipo(){
    delete[] jugadores;
}

//getters
string Equipo::getPais(){
    return pais;
}

int Equipo::getRanking(){
    return ranking;
}

int Equipo::getPuntos(){
    return puntos;
}
string Equipo::getDirectorTecnico(){
    return directorTecnico;
}
string Equipo::getConfederacion(){
    return confederacion;
}

//setters
void Equipo::setPais(const string& pais){
    this->pais=pais;
}

void Equipo::setConfederacion(const string& confederacion){
    this->confederacion=confederacion;
}

void Equipo::setDirectorTecnico(const string& dt){
    this->directorTecnico=dt;
}

void Equipo::setRanking(int ranking){
    this->ranking=ranking;
}

void Equipo::setFederacion(const string& federacion){
    this->federacion=federacion;
}

//agregar jugador
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

//estadísticas
void Equipo::actualizarEstadisticas(int golfavor,int golcontra,int amarillas,int rojas,int faltas,int resultadoPartido){
    golesFavor += golfavor;
    golesContra += golcontra;
    tarjetasAmarillas += amarillas;
    tarjetasRojas += rojas;
    this->faltas += faltas;

    if(resultadoPartido==1){
        partidosGanados++;
        puntos+=3;
    } else if(resultadoPartido==0){
        partidosEmpatados++;
        puntos+=1;
    } else if(resultadoPartido==-1){
        partidosPerdidos++;
    }
}

//mostrar
void Equipo::mostrarEquipo(){
    cout << "Pais: " << pais << endl;
    cout << "Ranking: " << ranking << endl;
    cout << "Confederacion: " << confederacion << endl;
    cout << "Director Tecnico: " << directorTecnico << endl;
    cout << "Puntos: " << puntos << endl;
    cout << "Goles Favor: " << golesFavor << " : " << golesContra << endl;
    cout << "Partidos Ganados: " << partidosGanados
         << " Partidos Empatados: " << partidosEmpatados
         << " Partidos Perdidos: " << partidosPerdidos << endl;
}


Equipo& Equipo::operator=(const Equipo& otro){
    if(this != &otro){
        pais = otro.pais;
        confederacion = otro.confederacion;
        federacion = otro.federacion;
        directorTecnico = otro.directorTecnico;

        ranking = otro.ranking;
        puntos = otro.puntos;

        golesFavor = otro.golesFavor;
        golesContra = otro.golesContra;
        partidosGanados = otro.partidosGanados;
        partidosEmpatados = otro.partidosEmpatados;
        partidosPerdidos = otro.partidosPerdidos;
        tarjetasAmarillas = otro.tarjetasAmarillas;
        tarjetasRojas = otro.tarjetasRojas;
        faltas = otro.faltas;

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
