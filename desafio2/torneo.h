#ifndef TORNEO_H
#define TORNEO_H
#include <string>
using namespace std;
class Equipo;
class Grupo;
class Partido;

class Torneo{
private:
    string nombre;
    string fechaInicio;
    int anio;

    Equipo* equipos;
    int cantidadEquipos;

    Grupo* grupos;
    int cantidadGrupos;

    Partido* partidos;
    int cantidadPartidos;

public:
    //constructores
    Torneo();
    Torneo(const Torneo& copia);

    //destructor
    ~Torneo();

    //getters
    string getNombre();
    int getAnio();
    string getFechaInicio();

    //Setters
    void setNombre(const string nombre);
    void setAnio(int anio);
    void setFechaInicio(const string fechaInicio);

    //metodos principales,
    void simularToneo();
    void generarEstadisticas();

    //despliegue
    void mostrarTorneo();
    //sobrecarga
    Torneo& operator=(const Torneo& otro);
};

#endif // TORNEO_H
