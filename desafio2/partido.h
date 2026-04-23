#ifndef PARTIDO_H
#define PARTIDO_H

#include <string>
using namespace std;

class Equipo;
class Jugador;

class Partido{
private:
    string fecha;
    string hora;

    string sede;
    string arbitros[3];

    Equipo* equipo1;
    Equipo* equipo2;

    int golesEquipo1;
    int golesEquipo2;

    float posesionEquipo1;
    float posesionEquipo2;

    Jugador** convocadosEquipo1;
    Jugador** convocadosEquipo2;
    int cantidadConvocados;

    int goleadoresEquipo1[20];
    int goleadoresEquipo2[20];

    int cantGoleadores1;
    int cantGoleadores2;

    float calcularLambda(float gf, float gc);
    int generarPoisson(float lambda);

    void convocarJugadores();
    void simularEventos(Jugador** jugadores, int golesEquipo, int* goleadores, int& cantGoleadores);
    void calcularPosesion();
    void actualizarEquipos();



public:
    Partido();
    Partido(const Partido& copia);
    ~Partido();

    Equipo* getEquipo1();
    Equipo* getEquipo2();
    string getFecha();
    string getHora();
    string getSede();
    string getArbitro(int i);
    int getGolesEquipo1();
    int getGolesEquipo2();

    void setFecha(const string& fecha);
    void setHora(const string& hora);
    void setSede(const string& sede);
    void setArbitros(const string arbitros[3]);
    void setEquipos(Equipo* equipo1, Equipo* equipo2);

    void simularPartido();
    void mostrarPartido();


    Partido& operator=(const Partido& otro);
};

#endif
