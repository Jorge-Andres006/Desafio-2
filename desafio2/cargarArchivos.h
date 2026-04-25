#ifndef CARGARARCHIVOS_H
#define CARGARARCHIVOS_H

#include "equipo.h"

string limpiarTexto(const string &texto);

int contarLineas(const string nombreArchivo);

string obtenerCampo(const string &linea, int &inicio);
void guardarEquiposCSV(const string &nombreArchivo,
                       Equipo *equipos,
                       int cantidadEquipos);
void guardarJugadoresCSV(const string &nombreArchivo, Equipo *equipos,
                         int cantidadEquipos);

void copiarArchivoCSV(const string &origen, const string &destino);

#endif // CARGARARCHIVOS_H
