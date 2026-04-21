#include "Partido.h"
#include "Equipo.h"
#include "Jugador.h"
#include <cmath>
#include <random>

using namespace std;

static std::mt19937 generador(std::random_device{}());

Partido::Partido(){
    equipo1 = NULL;
    equipo2 = NULL;

    golesEquipo1 = golesEquipo2 = 0;
    posesionEquipo1 = posesionEquipo2 = 0;

    faltasEquipo1 = faltasEquipo2 = 0;
    amarillasEquipo1 = amarillasEquipo2 = 0;
    rojasEquipo1 = rojasEquipo2 = 0;

    cantidadConvocados = 11;

    convocadosEquipo1 = new Jugador*[cantidadConvocados];
    convocadosEquipo2 = new Jugador*[cantidadConvocados];
}

Partido::Partido(const Partido& copia){
    fecha = copia.fecha;
    hora = copia.hora;
    sede = copia.sede;

    for(int i=0;i<3;i++) arbitros[i]=copia.arbitros[i];

    equipo1 = copia.equipo1;
    equipo2 = copia.equipo2;

    golesEquipo1 = copia.golesEquipo1;
    golesEquipo2 = copia.golesEquipo2;

    cantidadConvocados = copia.cantidadConvocados;

    convocadosEquipo1 = new Jugador*[cantidadConvocados];
    convocadosEquipo2 = new Jugador*[cantidadConvocados];

    for(int i=0;i<cantidadConvocados;i++){
        convocadosEquipo1[i]=copia.convocadosEquipo1[i];
        convocadosEquipo2[i]=copia.convocadosEquipo2[i];
    }
}

Partido::~Partido(){
    delete[] convocadosEquipo1;
    delete[] convocadosEquipo2;
}

//convocatoria
void Partido::convocarJugadores(){

    int usados1[50]={0};
    int usados2[50]={0};

    std::uniform_int_distribution<> dist1(0, equipo1->getCantidadJugadores()-1);
    std::uniform_int_distribution<> dist2(0, equipo2->getCantidadJugadores()-1);

    int contador=0;

    while(contador<cantidadConvocados){
        int indice = dist1(generador);
        if(!usados1[indice]){
            convocadosEquipo1[contador]=equipo1->getJugador(indice);
            usados1[indice]=1;
            contador++;
        }
    }

    contador=0;

    while(contador<cantidadConvocados){
        int indice = dist2(generador);
        if(!usados2[indice]){
            convocadosEquipo2[contador]=equipo2->getJugador(indice);
            usados2[indice]=1;
            contador++;
        }
    }
}

//lambda
float Partido::calcularLambda(float golesFavor,float golesContra){
    float mu=1.35;
    float alpha=0.6;
    float beta=0.4;

    return mu * pow(golesFavor/mu,alpha) * pow(golesContra/mu,beta);
}

//poisson
int Partido::generarPoisson(float lambda){

    std::uniform_real_distribution<> probabilidad(0.0,1.0);

    float limite = exp(-lambda);
    float producto=1.0;
    int contador=0;

    do{
        contador++;
        producto *= probabilidad(generador);
    }while(producto>limite);

    return contador-1;
}

//eventos
void Partido::simularEventos(Jugador** jugadores,int& goles,int& amarillas,int& rojas,int& faltas){

    std::uniform_int_distribution<> distJugador(0,cantidadConvocados-1);
    std::uniform_real_distribution<> probabilidad(0.0,1.0);

    for(int i=0;i<goles;i++){
        int indice=distJugador(generador);
        jugadores[indice]->actualizarEstadisticas(1,0,0,0,0);
    }

    for(int i=0;i<cantidadConvocados;i++){

        if(probabilidad(generador)<0.06){
            jugadores[i]->actualizarEstadisticas(0,0,1,0,0);
            amarillas++;
        }

        if(probabilidad(generador)<0.0115){
            jugadores[i]->actualizarEstadisticas(0,0,0,1,0);
            rojas++;
        }

        if(probabilidad(generador)<0.13){
            jugadores[i]->actualizarEstadisticas(0,0,0,0,1);
            faltas++;
        }

        jugadores[i]->actualizarEstadisticas(0,90,0,0,0);
    }
}

//actualizar equipos
void Partido::actualizarEquipos(){

    int resultadoEquipo1;
    int resultadoEquipo2;

    if(golesEquipo1 > golesEquipo2){
        resultadoEquipo1 = 1;
        resultadoEquipo2 = -1;
    }
    else if(golesEquipo1 < golesEquipo2){
        resultadoEquipo1 = -1;
        resultadoEquipo2 = 1;
    }
    else{
        resultadoEquipo1 = 0;
        resultadoEquipo2 = 0;
    }

    equipo1->actualizarEstadisticas(golesEquipo1,golesEquipo2,resultadoEquipo1);
    equipo2->actualizarEstadisticas(golesEquipo2,golesEquipo1,resultadoEquipo2);
}

