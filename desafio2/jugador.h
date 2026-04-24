#ifndef JUGADOR_H
#define JUGADOR_H

#include "estadisticajugador.h"
#include <string>
using namespace std;

class Jugador {
private:
    string nombre;
    string apellido;

    EstadisticaJugador estadisticas;

    int numero;

public:
    // Constructores
    Jugador();
    Jugador(const Jugador &copia); // constructor copia

    // Destructor
    ~Jugador();

    // Getters
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
    EstadisticaJugador &getEstadistica();
    // Setters
    void setNombre(const string nombre);
    void setApellido(const string apellido);
    void setNumero(int numero);

    // Operaciones principales
    void actualizarEstadisticas(int goles, int minutos, int amarillas, int rojas,
                                int faltas);
    void sumarPartido();

    // Despliegue
    void mostrarJugador();

    // Sobrecarga de operador
    Jugador &operator=(const Jugador &otro);
};

#endif // JUGADOR_Hf
