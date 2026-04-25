#include "InicializarDatos.h"
#include "cargarArchivos.h"
#include "jugador.h"
#include <fstream>
#include <iostream>
#include <string>
//Carga los equipos desde un archivo csv y devuelve un arreglo dinamico
Equipo *cargarEquipos(const string nombreArchivo, int &cantidadEquipos) {
    cantidadEquipos = contarLineas(nombreArchivo);
    ifstream archivo(nombreArchivo);

    if (!archivo) {
        cout << "Error abriendo archivo" << endl;
        return nullptr;
    }

    Equipo *equipos = new Equipo[cantidadEquipos];
    memoria += sizeof(Equipo) * cantidadEquipos;
    string linea;
    getline(archivo, linea);
    iteraciones++;
    int indiceEquipo = 0;
    while (getline(archivo, linea)) {
        iteraciones++;
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
            iteraciones++;
            string nombrePais = obtenerCampo(linea, posicion);
            iteraciones++;
            string directorTecnico = obtenerCampo(linea, posicion);
            iteraciones++;
            string nombreFederacion = obtenerCampo(linea, posicion);
            iteraciones++;
            string nombreConfederacion = obtenerCampo(linea, posicion);
            iteraciones++;

            int golesFavor = stoi(obtenerCampo(linea, posicion));
            iteraciones++;
            int golesContra = stoi(obtenerCampo(linea, posicion));
            iteraciones++;
            int partidosGanados = stoi(obtenerCampo(linea, posicion));
            iteraciones++;
            int partidosEmpatados = stoi(obtenerCampo(linea, posicion));
            iteraciones++;
            int partidosPerdidos = stoi(obtenerCampo(linea, posicion));
            iteraciones++;
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
//inicializa jugadores para cada equipo
void inicializarJugadoresEquipos(Equipo *equipos, int cantidadEquipos) {

    for (int i = 0; i < cantidadEquipos; i++) {
        iteraciones++;
        for (int j = 1; j <= 26; j++) {
        iteraciones++;
            Jugador jugador;
            jugador.setNombre("nombre" + to_string(j));
            jugador.setApellido("apellido" + to_string(j));
            jugador.setNumero(j);

            jugador.actualizarEstadisticas(0, 0, 0, 0, 0);

            equipos[i].agregarJugador(jugador);
        }
    }
}

