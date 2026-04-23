#ifndef ELIMINATORIA_H
#define ELIMINATORIA_H

#include "partido.h"
#include "equipo.h"
#include <string>

class Eliminatoria{
private:
    Partido* partidos;
    int cantidad;

public:
    Eliminatoria();
    Eliminatoria(const Eliminatoria& otra);
    ~Eliminatoria();

    Eliminatoria& operator=(const Eliminatoria& otra);

    int getCantidad();
    Partido* getPartidos();

    void agregarPartido(Equipo* equipo1, Equipo* equipo2);

    void crearDesdeClasificados(
        Equipo** equiposPrimeros,
        Equipo** equiposSegundos,
        Equipo** mejoresTerceros,
        char* grupoPrimeros,
        char* grupoSegundos,
        char* grupoMejoresTerceros
        );

    Equipo* simularPartidoEliminatoria(Partido& partido);
    Equipo* resolverEmpate(Partido& partido);

    Equipo** simularRonda(int& cantidadGanadores, const std::string& nombreRonda);
    Eliminatoria crearSiguienteRonda(Equipo** equipos, int cantidadEquipos);

    void mostrar();
};

#endif
