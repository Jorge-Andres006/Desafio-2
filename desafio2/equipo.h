#ifndef EQUIPO_H
#define EQUIPO_H

#include "estadisticaequipo.h"
#include <string>
using namespace std;

class Jugador;

class Equipo {
private:
    string pais;
    string confederacion;
    string federacion;
    string directorTecnico;

    EstadisticaEquipo estadisticas;

    Jugador *jugadores;
    int cantidadJugadores;
    int ranking;

public:
    // Constructores
    Equipo();
    Equipo(const Equipo &copia); // constructor copia

    // Destructor
    ~Equipo(); // libera jugadores[]

    // Getters
    string getPais()const;
    int getRanking()const;
    string getConfederacion()const;
    string getDirectorTecnico()const;
    string getFederacion()const;
    int getCantidadJugadores()const;
    Jugador *getJugador(int indice) const;
    EstadisticaEquipo &getEstadistica();
    int getGolesFavor();
    float getPromedioGolesFavor();
    float getPromedioGolesContra();

    // Setters
    void setPais(const string &pais);
    void setConfederacion(const string &confederacion);
    void setDirectorTecnico(const string &dt);
    void setRanking(int ranking);
    void setFederacion(const string &federacion);

    // Operaciones principales
    void agregarJugador(const Jugador &jugador);
    void actualizarEstadisticas(int golesFavor, int golesContra, int resultado);
    void cargarEstadisticas(int golesFavor, int golesContra, int partidosGanados,
                            int partidosEmpatados, int partidosPerdidos);

    // Despliegue
    void mostrarEquipo();

    // Sobrecarga de operador
    Equipo &operator=(const Equipo &otro);
};

#endif // EQUIPO_H
