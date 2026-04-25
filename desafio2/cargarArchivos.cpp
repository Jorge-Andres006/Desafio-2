#include "cargarArchivos.h"
#include "jugador.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
string obtenerCampo(const string &linea, int &inicio) {
    string campo = "";

    while (inicio < linea.size() && linea[inicio] != ';') {
        campo += linea[inicio];
        inicio++;
    }

    if (inicio < linea.size())
        inicio++;

    return campo;
}
string limpiarTexto(const string &texto) {
    string resultado = "";

    for (int i = 0; i < texto.size(); i++) {
        if (texto[i] != '\r') {
            resultado += texto[i];
        }
    }

    return resultado;
}
int contarLineas(const string nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo) {
        cout << "Error abriendo archivo" << endl;
        return 0;
    }

    string linea;
    int contador = 0;

    while (getline(archivo, linea)) {
        linea = limpiarTexto(linea);

        if (linea == "")
            continue;
        if (!isdigit(linea[0]))
            continue;

        contador++;
    }

    archivo.close();
    return contador;
}
void guardarEquiposCSV(const string &nombreArchivo,
                       Equipo *equipos,
                       int cantidadEquipos) {

    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "Error al crear el archivo" << endl;
        return;
    }

    archivo << "pais;confederacion;ranking;gf;gc;pg;pe;pp\n";

    for (int i = 0; i < cantidadEquipos; i++) {

        EstadisticaEquipo &est = equipos[i].getEstadistica();

        archivo << equipos[i].getPais() << ";"
                << equipos[i].getConfederacion() << ";"
                << equipos[i].getRanking() << ";"
                << est.getGolesFavor() << ";"
                << est.getGolesContra() << ";"
                << est.getPartidosGanados() << ";"
                << est.getPartidosEmpatados() << ";"
                << est.getPartidosPerdidos()
                << "\n";
    }

    archivo.close();
}
void guardarJugadoresCSV(const string &nombreArchivo, Equipo *equipos,
                         int cantidadEquipos) {

    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "Error al crear el archivo" << endl;
        return;
    }

    archivo << "pais;nombre;apellido;numero;goles;minutos;amarillas;rojas;faltas;"
               "asistencias;partidos\n";

    for (int i = 0; i < cantidadEquipos; i++) {

        for (int j = 0; j < equipos[i].getCantidadJugadores(); j++) {

            Jugador *jugador = equipos[i].getJugador(j);

            archivo << equipos[i].getPais() << ";" << jugador->getNombre() << ";"
                    << jugador->getApellido() << ";" << jugador->getNumero() << ";"
                    << jugador->getGoles() << ";" << jugador->getMinutos() << ";"
                    << jugador->getAmarillas() << ";" << jugador->getRojas() << ";"
                    << jugador->getFaltas() << ";" << jugador->getAsistencias() << ";"
                    << jugador->getPartidos() << "\n";
        }
    }

    archivo.close();
}
void copiarArchivoCSV(const string &origen, const string &destino) {

    ifstream archivoOrigen(origen);
    ofstream archivoDestino(destino);

    if (!archivoOrigen.is_open() || !archivoDestino.is_open()) {
        cout << "Error al abrir archivos" << endl;
        return;
    }

    string linea;

    while (getline(archivoOrigen, linea)) {
        archivoDestino << linea << "\n";
    }

    archivoOrigen.close();
    archivoDestino.close();
}
