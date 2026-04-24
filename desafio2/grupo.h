#ifndef GRUPO_H
#define GRUPO_H

class Equipo;
class Partido;

class Grupo {
private:
    Equipo **equipos;
    Partido *partidos;

    int cantidadEquipos;
    int cantidadPartidos;

    char letra;

public:
    // Constructores
    Grupo();
    Grupo(const Grupo &copia); // constructor copia

    // Destructor
    ~Grupo(); // libera equipos[] y partidos[]

    // Getters
    char getLetra();
    int getCantidadEquipos();
    int getCantidadPartidos();
    Equipo **getEquipos();
    Partido *getPartidos();

    // Setters
    void setLetra(char letra);

    // Operaciones principales
    void agregarEquipo(Equipo *equipo);
    void generarPartidos();

    // Despliegue
    void mostrarGrupo();

    // Sobrecarga de operador
    Grupo &operator=(const Grupo &otro);
};

#endif // GRUPO_H
