#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "estadisticaequipo.h"
using namespace std;

class Jugador;

class Equipo{
private:
    string pais;
    string confederacion;
    string federacion;
    string directorTecnico;

    int ranking;

    EstadisticaEquipo estadisticas;

    Jugador* jugadores;
    int cantidadJugadores;

public:
    Equipo();
    Equipo(const Equipo& copia);
    ~Equipo();

    string getPais();
    int getRanking();
    string getConfederacion();
    string getDirectorTecnico();

    void setPais(const string& pais);
    void setConfederacion(const string& confederacion);
    void setDirectorTecnico(const string& dt);
    void setRanking(int ranking);
    void setFederacion(const string& federacion);

    void agregarJugador(const Jugador& jugador);

    void actualizarEstadisticas(int gf,int gc,int resultado);


    void cargarEstadisticas(int gf,int gc,int pg,int pe,int pp);

    void mostrarEquipo();

    Equipo& operator=(const Equipo& otro);
};

#endif
