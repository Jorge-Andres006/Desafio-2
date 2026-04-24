#include "InicializarDatos.h"
#include "cargarArchivos.h"
#include "jugador.h"
#include <fstream>
#include <iostream>
#include <string>

Equipo *cargarEquipos(const string nombreArchivo, int &cantidadEquipos) {
    cantidadEquipos = contarLineas(nombreArchivo);

    ifstream archivo(nombreArchivo);

    if (!archivo) {
        cout << "Error abriendo archivo" << endl;
        return nullptr;
    }

    Equipo *equipos = new Equipo[cantidadEquipos];

    string linea;
    getline(archivo, linea);

    int indiceEquipo = 0;
    while (getline(archivo, linea)) {
        linea = limpiarTexto(linea);

        if (linea == "")
            continue;
        if (!isdigit(linea[0]))
            continue;

        if (indiceEquipo >= cantidadEquipos) {
            cout << "Error: demasiadas lineas" << endl;
            break;
        }

        int posicion = 0;

        try {
            int rankingFifa = stoi(obtenerCampo(linea, posicion));
            string nombrePais = obtenerCampo(linea, posicion);
            string directorTecnico = obtenerCampo(linea, posicion);
            string nombreFederacion = obtenerCampo(linea, posicion);
            string nombreConfederacion = obtenerCampo(linea, posicion);

            int golesFavor = stoi(obtenerCampo(linea, posicion));
            int golesContra = stoi(obtenerCampo(linea, posicion));
            int partidosGanados = stoi(obtenerCampo(linea, posicion));
            int partidosEmpatados = stoi(obtenerCampo(linea, posicion));
            int partidosPerdidos = stoi(obtenerCampo(linea, posicion));

            equipos[indiceEquipo].setPais(nombrePais);
            equipos[indiceEquipo].setDirectorTecnico(directorTecnico);
            equipos[indiceEquipo].setConfederacion(nombreConfederacion);
            equipos[indiceEquipo].setFederacion(nombreFederacion);
            equipos[indiceEquipo].setRanking(rankingFifa);

            equipos[indiceEquipo].cargarEstadisticas(
                golesFavor, golesContra, partidosGanados, partidosEmpatados,
                partidosPerdidos);

            indiceEquipo++;

        } catch (...) {
            cout << "Error en linea: " << linea << endl;
        }
    }

    archivo.close();
    return equipos;
}
void inicializarJugadoresEquipos(Equipo *equipos, int cantidadEquipos) {

    for (int i = 0; i < cantidadEquipos; i++) {

        for (int j = 1; j <= 26; j++) {

            Jugador jugador;

            jugador.setNombre("nombre" + to_string(j));
            jugador.setApellido("apellido" + to_string(j));
            jugador.setNumero(j);

            jugador.actualizarEstadisticas(0, 0, 0, 0, 0);

            equipos[i].agregarJugador(jugador);
        }
    }
}

void imprimirJugadoresEquipos(Equipo *equipos, int cantidadEquipos) {

    for (int i = 0; i < cantidadEquipos; i++) {

        cout << "======================" << endl;
        cout << "Equipo: " << equipos[i].getPais() << endl;

        for (int j = 0; j < equipos[i].getCantidadJugadores(); j++) {

            Jugador *jugador = equipos[i].getJugador(j);

            cout << jugador->getNombre() << " " << jugador->getApellido() << " - "
                 << jugador->getNumero() << endl;
        }
    }
}

void guardarEquipos(Equipo *equipos, int cantidadEquipos,
                    const string &nombreArchivo) {

    ofstream archivo(nombreArchivo);

    archivo << "Ranking,Pais,DT,Federacion,Confederacion,GF,GC,PG,PE,PP\n";

    for (int i = 0; i < cantidadEquipos; i++) {

        EstadisticaEquipo &est = equipos[i].getEstadistica();

        archivo << equipos[i].getRanking() << "," << equipos[i].getPais() << ","
                << equipos[i].getDirectorTecnico() << ","
                << equipos[i].getConfederacion() << ","
                << equipos[i].getConfederacion() << "," << est.getGolesFavor()
                << "," << est.getGolesContra() << "," << est.getPartidosGanados()
                << "," << est.getPartidosEmpatados() << ","
                << est.getPartidosPerdidos() << "\n";
    }

    archivo.close();
}

void guardarJugadores(Equipo *equipos, int cantidadEquipos,
                      const string &nombreArchivo) {

    ofstream archivo(nombreArchivo);

    archivo << "Pais,Numero,Nombre,Apellido,Partidos,Goles,Asistencias,Minutos,"
               "Amarillas,Rojas,Faltas\n";

    for (int i = 0; i < cantidadEquipos; i++) {

        for (int j = 0; j < equipos[i].getCantidadJugadores(); j++) {

            Jugador *jugador = equipos[i].getJugador(j);
            EstadisticaJugador &est = jugador->getEstadistica();

            archivo << equipos[i].getPais() << "," << jugador->getNumero() << ","
                    << jugador->getNombre() << "," << jugador->getApellido() << ","
                    << est.getPartidosJugados() << "," << est.getGoles() << ","
                    << est.getAsistencias() << "," << est.getMinutosJugados() << ","
                    << est.getTarjetasAmarillas() << "," << est.getTarjetasRojas()
                    << "," << est.getFaltas() << "\n";
        }
    }

    archivo.close();
}
