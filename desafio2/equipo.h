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

    //getters
    string getPais();
    int getRanking();
    string getConfederacion();
    string getDirectorTecnico();
    Jugador* getJugador(int indice);
    int getCantidadJugadores();

    //setters
    void setPais(const string& pais);
    void setConfederacion(const string& confederacion);
    void setDirectorTecnico(const string& dt);
    void setRanking(int ranking);
    void setFederacion(const string& federacion);

    //metodos
    void agregarJugador(const Jugador& jugador);
    void actualizarEstadisticas(int golesFavor,int golesContra,int resultado);
    void cargarEstadisticas(int golesFavor,int golesContra,int partidosGanados,int partidosEmpatados,int partidosPerdidos);
    float getPromedioGolesFavor();
    float getPromedioGolesContra();
    int getGolesFavor();
    void mostrarEquipo();
    EstadisticaEquipo& getEstadistica();
    Equipo& operator=(const Equipo& otro);
};

#endif
