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
    int faltasEquipo1;
    int faltasEquipo2;
    int amarillasEquipo1;
    int amarillasEquipo2;
    int rojasEquipo1;
    int rojasEquipo2;

    Jugador** convocadosEquipo1;
    Jugador** convocadosEquipo2;
    int cantidadConvocados;

public:
    //constructores
    Partido();
    Partido(const Partido& copia);

    //destructor
    ~Partido();

    //getters
    Equipo* getEquipo1();
    Equipo* getEquipo2();
    string getFecha();
    string getHora();
    string getSede();
    string getArbitro(int i);

    //setters
    void setFecha(const string fecha);
    void setEquipos(Equipo* equipo1, Equipo* equipo2);

    //metodos principales
    void convocarJugadores();
    void simularPartido();
    void actualizarEquipos();

    //despliegue
    void mostrarPartido();

    //sobrecarga
    Partido& operator=(const Partido& otro);

private:
    float calcularLambda(float golesFavor,float golesContra);
    int generarPoisson(float lambda);
    void simularEventos(Jugador** jugadores,int& goles,int& amarillas,int& rojas,int& faltas);
};

#endif
