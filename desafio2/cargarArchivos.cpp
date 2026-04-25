#include "cargarArchivos.h"
#include "jugador.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
//extraee un campo de una linea CSV usando ; como separador
string obtenerCampo(const string &linea, int &inicio) {
    memoria += sizeof(string);
    memoria += sizeof(int*);
    memoria += sizeof(string);
    string campo = "";

    while (inicio < linea.size() && linea[inicio] != ';') {
        iteraciones++;
        campo += linea[inicio];
        inicio++;
    }

    if (inicio < linea.size())
        inicio++;

    return campo;
}
//elimina caracteres de un texxto para evitar errores al leer archvios
string limpiarTexto(const string &texto) {
    memoria += sizeof(string);
    memoria += sizeof(string);
    string resultado = "";

    for (int i = 0; i < texto.size(); i++) {
        iteraciones++;
        if (texto[i] != '\r') {
            resultado += texto[i];
        }
    }

    return resultado;
}
//cuantas lineas validas que tiene un archivo CSV
int contarLineas(const string nombreArchivo) {
    memoria += sizeof(string);
    memoria += sizeof(ifstream);
    memoria += sizeof(string);
    memoria += sizeof(int);
    iteraciones++;
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
//la informacion de todos los equipos en un archivo csv
void guardarEquiposCSV(const string &nombreArchivo,
                       Equipo *equipos,
                       int cantidadEquipos) {
    memoria += sizeof(string);
    memoria += sizeof(Equipo*);
    memoria += sizeof(int);
    memoria += sizeof(ofstream);
    memoria += sizeof(EstadisticaEquipo);
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "Error al crear el archivo" << endl;
        return;
    }

    archivo << "pais;confederacion;ranking;gf;gc;pg;pe;pp\n";

    for (int i = 0; i < cantidadEquipos; i++) {
        iteraciones++;
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
//la informacion de todos los jugadores de todos los equipos en un CSV
void guardarJugadoresCSV(const string &nombreArchivo, Equipo *equipos,
                         int cantidadEquipos) {
    memoria += sizeof(string);
    memoria += sizeof(Equipo*);
    memoria += sizeof(int);
    memoria += sizeof(ofstream);
    memoria += sizeof(Jugador*);
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "Error al crear el archivo" << endl;
        return;
    }

    archivo << "pais;nombre;apellido;numero;goles;minutos;amarillas;rojas;faltas;"
               "asistencias;partidos\n";

    for (int i = 0; i < cantidadEquipos; i++) {
        iteraciones++;
        for (int j = 0; j < equipos[i].getCantidadJugadores(); j++){
            iteraciones++;
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
//copia todo el contenido de un archivo CSV a otro archivo
void copiarArchivoCSV(const string &origen, const string &destino) {
    memoria += sizeof(string);
    memoria += sizeof(string);
    memoria += sizeof(ifstream);
    memoria += sizeof(ofstream);
    memoria += sizeof(string);
    ifstream archivoOrigen(origen);
    ofstream archivoDestino(destino);

    if (!archivoOrigen.is_open() || !archivoDestino.is_open()) {
        cout << "Error al abrir archivos" << endl;
        return;
    }

    string linea;

    while (getline(archivoOrigen, linea)) {
        iteraciones++;
        archivoDestino << linea << "\n";
    }

    archivoOrigen.close();
    archivoDestino.close();
}
