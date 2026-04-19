#ifndef TORNEO_H
#define TORNEO_H
class Equipo;
class Grupo;
class Partido;

class Torneo{
private:
    char* nombre;
    char* fechaInicio;
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
    char* getNombre();
    int getAnio();
    char* getFechaInicio();

    //Setters
    void setNombre(const char* nombre);
    void setAnio(int anio);
    void setFechaInicio(const char* fechaInicio);

    //metodos principales,
    void simularToneo();
    void generarEstadisticas();

    //despliegue
    void mostrarTorneo();
    //sobrecarga
    Torneo& operator=(const Torneo& otro);
};

#endif // TORNEO_H
