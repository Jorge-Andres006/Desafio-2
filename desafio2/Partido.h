#ifndef PARTIDO_H
#define PARTIDO_H
class Equipo;
class Jugador;
class Partido{
private:
    char fecha[11];
    char hora[6];

    char sede[12];
    char arbitros[3][15];

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
    char* getFecha();
    char* getHora();
    char* getSede();
    char* getArbitro(int i);

    //setters
    void setFecha(const char* fecha);
    void setEquipos(Equipo* equipo1, Equipo* equipo2);

    //metodos principales
    void convocarJugadores();
    void simularPartido();
    void actualizarEquipos();

    //despliegue
    void mostrarPartido();

    //sobrecarga
    Partido& operator=(const Partido& otro);
};

#endif // PARTIDO_H
