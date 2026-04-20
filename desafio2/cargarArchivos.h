#ifndef CARGARARCHIVOS_H
#define CARGARARCHIVOS_H

#include "Equipo.h"

Equipo* cargarEquipos(const string nombreArchivo, int& cantidad);

int contarLineas(const string nombreArchivo);

#endif // CARGARARCHIVOS_H
