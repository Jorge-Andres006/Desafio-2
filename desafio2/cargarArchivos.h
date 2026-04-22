#ifndef CARGARARCHIVOS_H
#define CARGARARCHIVOS_H

#include "Equipo.h"

string limpiarTexto(const string& texto);
int contarLineas(const string nombreArchivo);
string obtenerCampo(const string& linea, int& inicio);
void guardarJugadoresCSV(const string& nombreArchivo, Equipo* equipos, int cantidadEquipos);
void copiarArchivoCSV(const string& origen, const string& destino);
#endif // CARGARARCHIVOS_H
