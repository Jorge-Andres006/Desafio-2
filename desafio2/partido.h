#ifndef PARTIDO_H
#define PARTIDO_H

#include <string>
using namespace std;

class Equipo;
class Jugador;

class Partido {
private:
    Equipo *equipo1;
    Equipo *equipo2;
    Jugador **convocadosEquipo1;
    Jugador **convocadosEquipo2;

    string fecha;
    string hora;
    string sede;
    string arbitros[3];

    float posesionEquipo1;
    float posesionEquipo2;

    int golesEquipo1;
    int golesEquipo2;
    int cantidadConvocados;
    int cantGoleadores1;
    int cantGoleadores2;
    int goleadoresEquipo1[20];
    int goleadoresEquipo2[20];

    float calcularLambda(float gf, float gc);
    int generarPoisson(float lambda);
    void convocarJugadores();
    void simularEventos(Jugador **jugadores, int golesEquipo, int *goleadores,
                        int &cantGoleadores, const string &nombreEquipo);
    void calcularPosesion();
    void actualizarEquipos();

public:
    // Constructores
    Partido();
    Partido(const Partido &copia); // constructor copia

    // Destructor
    ~Partido();

    // Getters
    Equipo *getEquipo1();
    Equipo *getEquipo2();
    string getFecha() const;
    string getHora() const;
    string getSede() const;
    string getArbitro(int i) const;
    int getGolesEquipo1() const;
    int getGolesEquipo2() const;
    Jugador **getConvocadosEquipo1();
    Jugador **getConvocadosEquipo2();

    // Setters
    void setFecha(const string &fecha);
    void setHora(const string &hora);
    void setSede(const string &sede);
    void setArbitros(const string arbitros[3]);
    void setEquipos(Equipo *equipo1, Equipo *equipo2);
    void setGoles(int g1, int g2);

    // Operaciones principales
    void simularPartido();

    // Despliegue
    void mostrarPartido();

    // Sobrecarga de operador
    Partido &operator=(const Partido &otro);
};

#endif // PARTIDO_H
