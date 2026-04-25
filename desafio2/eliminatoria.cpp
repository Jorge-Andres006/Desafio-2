#include "eliminatoria.h"
#include "cargarArchivos.h"
#include "jugador.h"
#include <iostream>
#include <random>

using namespace std;
//constructor
Eliminatoria::Eliminatoria() {
    cantidad = 0;
    partidos = nullptr;
}
//constructor de copia
Eliminatoria::Eliminatoria(const Eliminatoria &otra) {

    cantidad = otra.cantidad;

    if (cantidad > 0) {
        partidos = new Partido[cantidad];
        memoria += sizeof(Partido) * cantidad;
        for (int i = 0; i < cantidad; i++) {
            iteraciones++;
            partidos[i] = otra.partidos[i];
        }
    } else {
        partidos = nullptr;
    }
}
//destructor
Eliminatoria::~Eliminatoria() { delete[] partidos; }
//operador de sobrecarga
Eliminatoria &Eliminatoria::operator=(const Eliminatoria &otra) {

    if (this != &otra) {

        delete[] partidos;

        cantidad = otra.cantidad;

        if (cantidad > 0) {
            partidos = new Partido[cantidad];
            memoria += sizeof(Partido) * cantidad;
            for (int i = 0; i < cantidad; i++) {
                iteraciones++;
                partidos[i] = otra.partidos[i];
            }
        } else {
            partidos = nullptr;
        }
    }

    return *this;
}
//Getters
int Eliminatoria::getCantidad() const { return cantidad; }
Partido *Eliminatoria::getPartidos() const { return partidos; }

//verifica si dos equipos vienen del mismo grupo
bool Eliminatoria::mismoGrupo(char g1, char g2) { return g1 == g2; }
//agrega un nuevo partido a la eliminatoria aumentado el arreglo dinamico
void Eliminatoria::agregarPartido(Equipo *e1, Equipo *e2) {

    Partido *nuevo = new Partido[cantidad + 1];
     memoria += sizeof(Partido) * (cantidad + 1);
    for (int i = 0; i < cantidad; i++) {
        iteraciones++;
        nuevo[i] = partidos[i];
    }

    nuevo[cantidad].setEquipos(e1, e2);

    string arbitros[3] = {
        "codArbitro1", "codArbitro2", "codArbitro3"
    };

    nuevo[cantidad].setHora("00:00");
    nuevo[cantidad].setSede("nombreSede");
    nuevo[cantidad].setArbitros(arbitros);

    delete[] partidos;
    partidos = nuevo;

    cantidad++;
}
//crea los enfrentamiendos de la eliminatoria a partir de los equipos clasificados
void Eliminatoria::crearDesdeClasificados(Equipo **equiposPrimeros,
                                          Equipo **equiposSegundos,
                                          Equipo **mejoresTerceros,
                                          char *grupoPrimeros,
                                          char *grupoSegundos,
                                          char *grupoMejoresTerceros) {

    bool usadosTerceros[8] = {false};
    bool usadosSegundos[12] = {false};

    int idx;

    for (int i = 0; i < 8; i++) {
        iteraciones++;
        idx = -1;
        for (int j = 0; j < 8; j++) {
            iteraciones++;
            if (!usadosTerceros[j] &&
                grupoMejoresTerceros[j] != grupoPrimeros[i]) {
                idx = j;
                break;
            }
        }
        if (idx == -1) {
            for (int j = 0; j < 8; j++) {
                iteraciones++;
                if (!usadosTerceros[j]) {
                    idx = j;
                    break;
                }
            }
        }
        agregarPartido(equiposPrimeros[i], mejoresTerceros[idx]);
        usadosTerceros[idx] = true;
    }

    for (int i = 8; i < 12; i++) {
        iteraciones++;

        idx = -1;

        for (int j = 0; j < 12; j++) {
            iteraciones++;
            if (!usadosSegundos[j] &&
                grupoSegundos[j] != grupoPrimeros[i]) {
                idx = j;
                break;
            }
        }
        if (idx == -1) {
            for (int j = 0; j < 12; j++) {
                if (!usadosSegundos[j]) {
                    idx = j;
                    break;
                }
            }
        }

        agregarPartido(equiposPrimeros[i], equiposSegundos[idx]);
        usadosSegundos[idx] = true;
    }
    for (int i = 0; i < 12; i++) {
        iteraciones++;
        if (usadosSegundos[i])
            continue;

        for (int j = i + 1; j < 12; j++) {
            iteraciones++;
            if (usadosSegundos[j])
                continue;

            if (grupoSegundos[i] != grupoSegundos[j]) {

                agregarPartido(equiposSegundos[i], equiposSegundos[j]);
                usadosSegundos[i] = true;
                usadosSegundos[j] = true;
                break;
            }
        }
        if (!usadosSegundos[i]) {
            for (int j = i + 1; j < 12; j++) {
                iteraciones++;
                if (!usadosSegundos[j]) {
                    agregarPartido(equiposSegundos[i], equiposSegundos[j]);
                    usadosSegundos[i] = true;
                    usadosSegundos[j] = true;
                    break;
                }
            }
        }
    }
}
//simula un partido eliminatorio y devuelve el equipo ganador
Equipo *Eliminatoria::simularPartidoEliminatoria(Partido &partido) {

    partido.setFecha("2026-07-10");

    partido.simularPartido();

    int goles1 = partido.getGolesEquipo1();
    int goles2 = partido.getGolesEquipo2();

    partido.mostrarPartido();

    if (goles1 > goles2) {
        return partido.getEquipo1();
    }

    if (goles2 > goles1) {
        return partido.getEquipo2();
    }

    cout << ">> Empate en 90 minutos. Se juega prorroga...\n";

    Equipo *ganador = resolverEmpate(partido);

    if (ganador == partido.getEquipo1()) {
        goles1++;
    } else {
        goles2++;
    }

    partido.setGoles(goles1, goles2);

    cout << ">> Resultado final: "
         << partido.getEquipo1()->getPais() << " "
         << goles1 << " - " << goles2 << " "
         << partido.getEquipo2()->getPais()
         << " (prorroga)\n";

    Jugador **conv1 = partido.getConvocadosEquipo1();
    Jugador **conv2 = partido.getConvocadosEquipo2();

    for (int i = 0; i < 11; i++) {

        if (conv1[i] != nullptr) {
            conv1[i]->actualizarEstadisticas(0, 30, 0, 0, 0);
        }

        if (conv2[i] != nullptr) {
            conv2[i]->actualizarEstadisticas(0, 30, 0, 0, 0);
        }
    }

    return ganador;
}
//resuelve un empate usando probabilidad basada en el ranking de los equipos
Equipo *Eliminatoria::resolverEmpate(Partido &partido) {

    Equipo *equipo1 = partido.getEquipo1();
    Equipo *equipo2 = partido.getEquipo2();

    int ranking1 = equipo1->getRanking();
    int ranking2 = equipo2->getRanking();

    float inv1 = 1.0f / ranking1;
    float inv2 = 1.0f / ranking2;

    float total = inv1 + inv2;

    float prob1 = inv1 / total;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    float r = dist(gen);

    if (r < prob1) {
        return equipo1;
    } else {
        return equipo2;
    }
}
//crea la siguiente ronda emparejando los equipos ganadores
Eliminatoria Eliminatoria::crearSiguienteRonda(Equipo **equipos,
                                               int cantidadEquipos) {

    Eliminatoria nueva;

    if (equipos == nullptr || cantidadEquipos <= 1) {
        cout << "Error creando siguiente ronda\n";
        return nueva;
    }

    for (int i = 0; i < cantidadEquipos - 1; i += 2) {
        iteraciones++;
        if (equipos[i] == nullptr || equipos[i + 1] == nullptr) {
            cout << "Error: equipo NULL en emparejamiento\n";
            continue;
        }

        nueva.agregarPartido(equipos[i], equipos[i + 1]);
    }

    return nueva;
}
//muestra en pantalla todos los partidos de la eliminatoria
void Eliminatoria::mostrar() const {

    cout << "\n===== DIECISEISAVOS =====\n";

    for (int i = 0; i < cantidad; i++) {
        iteraciones++;
        cout << partidos[i].getEquipo1()->getPais() << " vs "
             << partidos[i].getEquipo2()->getPais() << endl;
    }
}
//simula toda la ronda y devuelve un arreglo con los equipos ganadores
Equipo **Eliminatoria::simularRonda(int &cantidadGanadores,
                                    const string &nombreRonda) {

    cout << "\n====== " << nombreRonda << " ======\n";

    if (cantidad <= 0) {
        cout << "Error: no hay partidos en esta ronda\n";
        cantidadGanadores = 0;
        return nullptr;
    }

    cantidadGanadores = cantidad;

    Equipo **ganadores = new Equipo *[cantidadGanadores];
    memoria += sizeof(Equipo*) * cantidadGanadores;
    for (int i = 0; i < cantidad; i++) {
        iteraciones++;
        if (partidos == nullptr) {
            cout << "Error: partidos NULL\n";
            ganadores[i] = nullptr;
            continue;
        }

        if (partidos[i].getEquipo1() == nullptr ||
            partidos[i].getEquipo2() == nullptr) {

            cout << "Error: equipos NULL en partido " << i << endl;
            ganadores[i] = nullptr;
            continue;
        }

        Equipo *ganador = simularPartidoEliminatoria(partidos[i]);

        if (ganador == nullptr) {
            cout << "Error: ganador NULL en partido " << i << endl;
        }

        ganadores[i] = ganador;

        cout << endl;
    }

    return ganadores;
}
