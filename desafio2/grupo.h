#ifndef GRUPO_H
#define GRUPO_H

class Equipo;
class Partido;

class Grupo{
private:
    char letra;

    Equipo** equipos;
    int cantidadEquipos;

    Partido* partidos;
    int cantidadPartidos;

public:
    Grupo();
    Grupo(const Grupo& copia);
    ~Grupo();

    char getLetra();
    int getCantidadEquipos();

    void setLetra(char letra);

    void agregarEquipo(Equipo* equipo);
    void generarPartidos();

    Equipo** getEquipos();
    int getCantidadPartidos();
    Partido* getPartidos();

    void mostrarGrupo();

    Grupo& operator=(const Grupo& otro);
};

#endif
