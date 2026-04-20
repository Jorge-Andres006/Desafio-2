#ifndef TORNEO_H
#define TORNEO_H

#include <string>

class Equipo;
class Grupo;
class Partido;

class Torneo{
private:
    std::string nombre;
    std::string fechaInicio;
    int anio;

    Equipo** equipos;
    int cantidadEquipos;

    Grupo* grupos;
    int cantidadGrupos;

    //bombos
    Equipo** bombo1;
    Equipo** bombo2;
    Equipo** bombo3;
    Equipo** bombo4;

    //metodos internos
    void ordenarPorRanking();
    void conformarBombos();
    bool sorteo();
    int sortearDeBombo(Equipo** bombo, bool* usado, int tamano, Grupo& grupo);
    bool esValido(Grupo& grupo, Equipo* equipo);

public:
    Torneo();
    Torneo(const Torneo& otro);
    ~Torneo();

    Torneo& operator=(const Torneo& otro);

    void setEquipos(Equipo** equipos, int cantidad);
    void inicializarGrupos(int cantidad);

    void simularTorneo();
    void mostrarGrupos();
    void mostrarBombos();

    Grupo* getGrupos();
    int getCantidadGrupos();
};

#endif
