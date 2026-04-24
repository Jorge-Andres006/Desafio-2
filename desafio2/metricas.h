#ifndef METRICAS_H
#define METRICAS_H

#include "eliminatoria.h"
#include "equipo.h"
#include "grupo.h"
#include <string>
using namespace std;

class Metricas {
private:
    static long long iteraciones;

public:
    static void resetIteraciones();

    static void sumarIteraciones(long long n);

    static long long getIteraciones();

    static long long calcularMemoriaEquipos(Equipo *equipos, int cantidadEquipos);

    static long long calcularMemoriaGrupos(Grupo *grupos, int cantidadGrupos);

    static long long calcularMemoriaEliminatoria(const Eliminatoria &elim);

    static long long calcularMemoriaTotal(Equipo *equipos, int cantidadEquipos,
                                          Grupo *grupos, int cantidadGrupos);

    static void reportar(const string &nombreFuncionalidad, Equipo *equipos,
                         int cantidadEquipos, Grupo *grupos, int cantidadGrupos);
};

#endif // METRICAS_H
