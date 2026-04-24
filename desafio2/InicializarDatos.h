#ifndef INICIALIZARDATOS_H
#define INICIALIZARDATOS_H

#include "equipo.h"

Equipo *cargarEquipos(const string nombreArchivo, int &cantidad);

void inicializarJugadoresEquipos(Equipo *equipos, int cantidadEquipos);

void imprimirJugadoresEquipos(Equipo *equipos, int cantidadEquipos);

void guardarEquipos(Equipo *equipos, int cantidadEquipos,
                    const string &nombreArchivo);

void guardarJugadores(Equipo *equipos, int cantidadEquipos,
                      const string &nombreArchivo);

#endif // INICIALIZARDATOS_H
