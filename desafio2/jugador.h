#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "estadisticajugador.h"
using namespace std;

class Jugador{
private:
    string nombre;
    string apellido;
    int numero;

    EstadisticaJugador estadisticas;

public:
    //constructores
    Jugador();
    Jugador(const Jugador& copia);

    //destructor
    ~Jugador();

    //getters
    string getNombre();
    string getApellido();
    int getNumero();
    int getGoles();
    int getMinutos();
    int getAmarillas();
    int getRojas();
    int getFaltas();
    int getAsistencias();
    int getPartidos();


    //setters
    void setNombre(const string nombre);
    void setApellido(const string apellido);
    void setNumero(int numero);

    //metodos principales
    void actualizarEstadisticas(int goles, int minutos, int amarillas, int rojas, int faltas);
    void sumarPartido();
    //despliegue
    void mostrarJugador();

    //sobrecarga
    Jugador& operator=(const Jugador& otro);
};

#endif
