#ifndef INICIALIZARDATOS_H
#define INICIALIZARDATOS_H

#include "equipo.h"

Equipo *cargarEquipos(const string nombreArchivo, int &cantidad);

void inicializarJugadoresEquipos(Equipo *equipos, int cantidadEquipos);


#endif // INICIALIZARDATOS_H
