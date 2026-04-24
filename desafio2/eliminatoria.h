#ifndef ELIMINATORIA_H
#define ELIMINATORIA_H

#include "equipo.h"
#include "partido.h"
#include <string>

class Eliminatoria {
private:
    Partido *partidos;
    int cantidad;

public:
    // Constructores
    Eliminatoria();
    Eliminatoria(const Eliminatoria &otra); // constructor copia

    // Destructor
    ~Eliminatoria(); // libera partidos[]

    // Getters
    int getCantidad();
    Partido *getPartidos();

    // Operaciones principales
    void agregarPartido(Equipo *equipo1, Equipo *equipo2);

    void crearDesdeClasificados(Equipo **equiposPrimeros,
                                Equipo **equiposSegundos,
                                Equipo **mejoresTerceros, char *grupoPrimeros,
                                char *grupoSegundos, char *grupoMejoresTerceros);
    Equipo *simularPartidoEliminatoria(Partido &partido);
    Equipo *resolverEmpate(Partido &partido);

    Equipo **simularRonda(int &cantidadGanadores, const string &nombreRonda);
    Eliminatoria crearSiguienteRonda(Equipo **equipos, int cantidadEquipos);

    // Despliegue
    void mostrar();

    bool mismoGrupo(char g1, char g2);

    // Sobrecarga de operador
    Eliminatoria &
    operator=(const Eliminatoria &otra); // copia profunda de partidos
};

#endif // ELIMINATORIA_H
