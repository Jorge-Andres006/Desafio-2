#include "metricas.h"
#include "jugador.h"
#include "partido.h"
#include <iostream>
using namespace std;


long long Metricas::iteraciones = 0;



void Metricas::resetIteraciones() {
    iteraciones = 0;
}

void Metricas::sumarIteraciones(long long n) {
    iteraciones += n;
}

long long Metricas::getIteraciones() {
    return iteraciones;
}


long long Metricas::calcularMemoriaEquipos(Equipo *equipos, int cantidadEquipos) {
    if (!equipos) return 0;


    long long total = (long long)sizeof(Equipo) * cantidadEquipos;

    for (int i = 0; i < cantidadEquipos; i++) {
        int nj = equipos[i].getCantidadJugadores();
        if (nj > 0) {

            total += (long long)sizeof(Jugador) * nj;
        }
    }

    return total;
}


long long Metricas::calcularMemoriaGrupos(Grupo *grupos, int cantidadGrupos) {
    if (!grupos) return 0;

    long long total = (long long)sizeof(Grupo) * cantidadGrupos;

    for (int i = 0; i < cantidadGrupos; i++) {
        int ne = grupos[i].getCantidadEquipos();
        int np = grupos[i].getCantidadPartidos();


        if (ne > 0) total += (long long)sizeof(Equipo *) * ne;


        if (np > 0) total += (long long)sizeof(Partido) * np;
    }

    return total;
}


long long Metricas::calcularMemoriaEliminatoria(const Eliminatoria &elim) {
    long long total = sizeof(Eliminatoria);

    total += (long long)sizeof(Partido) * 32;
    return total;
}


long long Metricas::calcularMemoriaTotal(Equipo *equipos, int cantidadEquipos,
                                         Grupo *grupos, int cantidadGrupos) {
    long long total = 0;


    total += (long long)sizeof(Equipo *) * cantidadEquipos;


    total += calcularMemoriaEquipos(equipos, cantidadEquipos);

    total += calcularMemoriaGrupos(grupos, cantidadGrupos);

    return total;
}



void Metricas::reportar(const string &nombreFuncionalidad,
                        Equipo *equipos, int cantidadEquipos,
                        Grupo *grupos, int cantidadGrupos) {

    long long mem = calcularMemoriaTotal(equipos, cantidadEquipos, grupos, cantidadGrupos);

    cout << "\n---------- METRICAS: " << nombreFuncionalidad << " ----------\n";
    cout << "Iteraciones realizadas : " << iteraciones << "\n";
    cout << "Memoria consumida      : " << mem << " bytes";

    if (mem >= 1024 * 1024)
        cout << " (" << mem / (1024 * 1024) << " MB)";
    else if (mem >= 1024)
        cout << " (" << mem / 1024 << " KB)";

    cout << "\n";
    cout << "---------------------------------------------------\n\n";
}
