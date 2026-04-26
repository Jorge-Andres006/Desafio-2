#include "torneo.h"
#include "eliminatoria.h"
#include "equipo.h"
#include "grupo.h"
#include "jugador.h"
#include "partido.h"
#include "tablagrupo.h"
#include <iostream>
#include <random>
using namespace std;

int aleatorio(int limite) {
    if(limite<=0) return 0;
    static random_device rd;
    static mt19937 gen(random_device{}());
    uniform_int_distribution<> dist(0, limite - 1);
    return dist(gen);
}

// constructor
Torneo::Torneo() {
    equipos = nullptr;
    cantidadEquipos = 0;

    grupos = nullptr;
    cantidadGrupos = 0;

    bombo1 = bombo2 = bombo3 = bombo4 = nullptr;

    ganadores16 = nullptr;
    ganadores8 = nullptr;
    ganadores4 = nullptr;
    ganadores2 = nullptr;
    campeon = nullptr;
    perdedoresSemis = nullptr;
    perdedoresFinal = nullptr;
}

// destructor
Torneo::~Torneo() {

    if (ganadores16) delete[] ganadores16;
    if (ganadores8) delete[] ganadores8;
    if (ganadores4) delete[] ganadores4;
    if (ganadores2) delete[] ganadores2;
    if (campeon) delete[] campeon;

    if (perdedoresSemis) delete[] perdedoresSemis;
    if (perdedoresFinal) delete[] perdedoresFinal;

    if (grupos) delete[] grupos;

    if (bombo1) delete[] bombo1;
    if (bombo2) delete[] bombo2;
    if (bombo3) delete[] bombo3;
    if (bombo4) delete[] bombo4;
}
Torneo& Torneo::operator=(const Torneo &otro) {

    if (this != &otro) {

        if (grupos) delete[] grupos;

        if (ganadores16) delete[] ganadores16;
        if (ganadores8) delete[] ganadores8;
        if (ganadores4) delete[] ganadores4;
        if (ganadores2) delete[] ganadores2;
        if (campeon) delete[] campeon;
        if (perdedoresSemis) delete[] perdedoresSemis;
        if (perdedoresFinal) delete[] perdedoresFinal;

        equipos = otro.equipos;
        cantidadEquipos = otro.cantidadEquipos;

        nombre = otro.nombre;
        fechaInicio = otro.fechaInicio;
        anio = otro.anio;

        cantidadGrupos = otro.cantidadGrupos;

        if (cantidadGrupos > 0) {
            grupos = new Grupo[cantidadGrupos];
            for (int i = 0; i < cantidadGrupos; i++) {
                grupos[i] = otro.grupos[i];
            }
        } else {
            grupos = nullptr;
        }

        bombo1 = nullptr;
        bombo2 = nullptr;
        bombo3 = nullptr;
        bombo4 = nullptr;

        dieciseisavos = otro.dieciseisavos;
        octavos = otro.octavos;
        cuartos = otro.cuartos;
        semis = otro.semis;
        final = otro.final;

        ganadores16 = nullptr;
        ganadores8 = nullptr;
        ganadores4 = nullptr;
        ganadores2 = nullptr;
        campeon = nullptr;
        perdedoresSemis = nullptr;
        perdedoresFinal = nullptr;

        cant16 = cant8 = cant4 = cant2 = cant1 = 0;
    }

    return *this;
}
// set equipos
void Torneo::setEquipos(Equipo **equipos, int cantidad) {
    this->equipos = equipos;
    this->cantidadEquipos = cantidad;
}

void Torneo::inicializarGrupos(int cantidad) {

    if (grupos) delete[] grupos;

    cantidadGrupos = cantidad;
    grupos = new Grupo[cantidadGrupos];
    memoria += sizeof(Grupo) * cantidadGrupos;

    for (int i = 0; i < cantidadGrupos; i++) {
        iteraciones++;
        grupos[i].setLetra('A' + i);
    }
}
void Torneo::conformarBombos() {

    delete[] bombo1;
    delete[] bombo2;
    delete[] bombo3;
    delete[] bombo4;

    ordenarPorRanking();

    bombo1 = new Equipo*[12];
    bombo2 = new Equipo*[12];
    bombo3 = new Equipo*[12];
    bombo4 = new Equipo*[12];
    memoria += sizeof(Equipo*) * 12 * 4;

    int i1 = 0, i2 = 0, i3 = 0, i4 = 0;

    int idxUSA = -1;

    for (int i = 0; i < cantidadEquipos; i++) {
        iteraciones++;
        if (equipos[i]->getPais() == "United States") {
            bombo1[i1++] = equipos[i];
            idxUSA = i;
            break;
        }
    }

    for (int i = 0; i < cantidadEquipos; i++) {
        iteraciones++;
        if (i == idxUSA) continue;

        if (i1 < 12)
            bombo1[i1++] = equipos[i];
        else if (i2 < 12)
            bombo2[i2++] = equipos[i];
        else if (i3 < 12)
            bombo3[i3++] = equipos[i];
        else
            bombo4[i4++] = equipos[i];
    }
}
// sacar equipo de un bombo
int Torneo::sortearDeBombo(Equipo **bombo, bool *usado, int tamano, Grupo &grupo) {

    int indices[12];
    int n = 0;
    memoria += sizeof(int) * 12;

    for (int i = 0; i < tamano; i++) {
        iteraciones++;
        if (!usado[i]) {
            indices[n++] = i;
        }
    }

    for (int i = 0; i < n; i++) {
        iteraciones++;
        int j = aleatorio(n);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }
    for (int i = 0; i < n; i++) {
        iteraciones++;
        int idx = indices[i];

        if (esValido(grupo, bombo[idx])) {
            grupo.agregarEquipo(bombo[idx]);
            usado[idx] = true;
            return 1;
        }
    }

    return 0;
}
bool Torneo::sorteo() {

    bool usado1[12] = {false};
    bool usado2[12] = {false};
    bool usado3[12] = {false};
    bool usado4[12] = {false};
    memoria+=sizeof(bool)*12*4;
    for (int i = 0; i < cantidadGrupos; i++) {
        iteraciones++;
        grupos[i] = Grupo();
        grupos[i].setLetra('A' + i);
    }

    for (int i = 0; i < cantidadGrupos; i++) {
        iteraciones++;
        if (!sortearDeBombo(bombo1, usado1, 12, grupos[i]))
            return false;
        if (!sortearDeBombo(bombo2, usado2, 12, grupos[i]))
            return false;
        if (!sortearDeBombo(bombo3, usado3, 12, grupos[i]))
            return false;
        if (!sortearDeBombo(bombo4, usado4, 12, grupos[i]))
            return false;
    }

    return true;
}
void Torneo::realizarSorteo() {
    conformarBombos();
    while (!sorteo()) {
        iteraciones++;
    }
}
void Torneo::mostrarBombos() const {
    cout << "====== Bombo 1 ======" << endl;
    for (int i = 0; i < 12; i++) {
        iteraciones++;
        cout << bombo1[i]->getPais() << " - " << bombo1[i]->getConfederacion()
        << endl;
    }

    cout << endl;

    cout << "====== Bombo 2 ======" << endl;
    for (int i = 0; i < 12; i++) {
        iteraciones++;
        cout << bombo2[i]->getPais() << " - " << bombo2[i]->getConfederacion()
        << endl;
    }

    cout << endl;

    cout << "====== Bombo 3 ======" << endl;
    for (int i = 0; i < 12; i++) {
        iteraciones++;
        cout << bombo3[i]->getPais() << " - " << bombo3[i]->getConfederacion()
        << endl;
    }

    cout << endl;

    cout << "====== Bombo 4 ======" << endl;
    for (int i = 0; i < 12; i++) {
        iteraciones++;
        cout << bombo4[i]->getPais() << " - " << bombo4[i]->getConfederacion()
        << endl;
    }

    cout << endl;
}
// validar confederaciones
bool Torneo::esValido(Grupo &grupo, Equipo *nuevo) {

    int contadorUEFA = 0;

    Equipo **lista = grupo.getEquipos();

    for (int i = 0; i < grupo.getCantidadEquipos(); i++) {
        iteraciones++;
        if (lista[i]->getConfederacion() == nuevo->getConfederacion()) {

            if (nuevo->getConfederacion() == "UEFA") {
                contadorUEFA++;
                if (contadorUEFA >= 2)
                    return false;
            } else {
                return false;
            }
        }
    }

    return true;
}

void Torneo::mostrarGrupos() const {
    for (int i = 0; i < cantidadGrupos; i++) {
        iteraciones++;
        grupos[i].mostrarGrupo();
    }
}
void Torneo::ordenarPorRanking() {

    for (int i = 0; i < cantidadEquipos - 1; i++) {
        iteraciones++;
        bool cambio = false;
        for (int j = 0; j < cantidadEquipos - i - 1; j++) {
        iteraciones++;
            if (equipos[j] && equipos[j + 1] &&
                equipos[j]->getRanking() > equipos[j + 1]->getRanking()) {

                Equipo *aux = equipos[j];
                equipos[j] = equipos[j + 1];
                equipos[j + 1] = aux;

                cambio = true;
            }
        }
        if (!cambio) break;
    }
}
Grupo *Torneo::getGrupos() const {
    return grupos;
}
int Torneo::getCantidadGrupos() const {
    return cantidadGrupos;
}
void Torneo::asignarFechasGrupos() {

    int partidosPorDia[19] = {0};
    int ultimoDia[48];
    memoria += sizeof(int) * (19 + 48);
    for (int i = 0; i < 48; i++){
        iteraciones++;
        ultimoDia[i] = -10;
    }
    for (int g = 0; g < cantidadGrupos; g++) {
        iteraciones++;
        Partido *partidos = grupos[g].getPartidos();
        int cantidad = grupos[g].getCantidadPartidos();

        for (int i = 0; i < cantidad; i++) {
            iteraciones++;
            Equipo *e1 = partidos[i].getEquipo1();
            Equipo *e2 = partidos[i].getEquipo2();

            int id1 = -1, id2 = -1;

            for (int k = 0; k < cantidadEquipos; k++) {
                iteraciones++;
                if (equipos[k] == e1)
                    id1 = k;
                if (equipos[k] == e2)
                    id2 = k;
            }

            bool asignado = false;

            for (int d = 0; d < 19; d++) {
                iteraciones++;
                if (partidosPorDia[d] >= 4)
                    continue;
                if (d - ultimoDia[id1] < 3)
                    continue;
                if (d - ultimoDia[id2] < 3)
                    continue;

                int dia = 20 + d;

                string fecha;

                if (dia <= 30) {
                    if (dia < 10)
                        fecha = "2026-06-0" + to_string(dia);
                    else
                        fecha = "2026-06-" + to_string(dia);
                } else {
                    int dj = dia - 30;
                    if (dj < 10)
                        fecha = "2026-07-0" + to_string(dj);
                    else
                        fecha = "2026-07-" + to_string(dj);
                }

                partidos[i].setFecha(fecha);

                partidosPorDia[d]++;
                ultimoDia[id1] = d;
                ultimoDia[id2] = d;

                asignado = true;
                break;
            }

            if (!asignado) {

                for (int d = 0; d < 19; d++) {
                    iteraciones++;
                    if (partidosPorDia[d] >= 4)
                        continue;

                    int dia = 20 + d;

                    string fecha;

                    if (dia <= 30) {
                        if (dia < 10)
                            fecha = "2026-06-0" + to_string(dia);
                        else
                            fecha = "2026-06-" + to_string(dia);
                    } else {
                        int dj = dia - 30;
                        if (dj < 10)
                            fecha = "2026-07-0" + to_string(dj);
                        else
                            fecha = "2026-07-" + to_string(dj);
                    }

                    partidos[i].setFecha(fecha);

                    partidosPorDia[d]++;
                    ultimoDia[id1] = d;
                    ultimoDia[id2] = d;

                    break;
                }
            }
        }
    }
}
void Torneo::mostrarTablasGrupos() const {

    for (int i = 0; i < cantidadGrupos; i++) {
        iteraciones++;
        cout << "\n======================" << endl;
        cout << "GRUPO " << char('A' + i) << endl;
        cout << "======================" << endl;

        TablaGrupo tabla(grupos[i]);

        tabla.calcularPuntos();
        tabla.ordenarTabla();
        tabla.mostrarTabla();
    }
}

void Torneo::obtenerClasificados(Equipo **&equiposPrimeros,
                                 Equipo **&equiposSegundos,
                                 Equipo **&equiposTerceros,
                                 char *&grupoPrimeros,
                                 char *&grupoSegundos,
                                 char *&grupoTerceros) {


    equiposPrimeros = new Equipo*[12];
    equiposSegundos = new Equipo*[12];
    equiposTerceros = new Equipo*[12];

    grupoPrimeros = new char[12];
    grupoSegundos = new char[12];
    grupoTerceros = new char[12];
    memoria += sizeof(Equipo*) * 12 * 3;
    memoria += sizeof(char) * 12 * 3;
    for (int i = 0; i < 12; i++) {
        iteraciones++;
        TablaGrupo tabla(grupos[i]);

        tabla.calcularPuntos();
        tabla.ordenarTabla();

        equiposPrimeros[i] = tabla.getEquipo(0);
        equiposSegundos[i] = tabla.getEquipo(1);
        equiposTerceros[i] = tabla.getEquipo(2);

        grupoPrimeros[i] = 'A' + i;
        grupoSegundos[i] = 'A' + i;
        grupoTerceros[i] = 'A' + i;
    }
}

void Torneo::ordenarTerceros(Equipo **equiposTerceros, int *puntos,
                             int *diferenciaGol, int *golesFavor,
                             char *grupos) {

    for (int i = 0; i < 11; i++) {
        iteraciones++;
        for (int j = 0; j < 11 - i; j++) {
            iteraciones++;

            bool cambiar = false;

            if (puntos[j] < puntos[j + 1])
                cambiar = true;
            else if (puntos[j] == puntos[j + 1] &&
                     diferenciaGol[j] < diferenciaGol[j + 1])
                cambiar = true;
            else if (puntos[j] == puntos[j + 1] &&
                     diferenciaGol[j] == diferenciaGol[j + 1] &&
                     golesFavor[j] < golesFavor[j + 1])
                cambiar = true;
            else if (puntos[j] == puntos[j + 1] &&
                     diferenciaGol[j] == diferenciaGol[j + 1] &&
                     golesFavor[j] == golesFavor[j + 1] && rand() % 2)
                cambiar = true;

            if (cambiar) {

                Equipo *tempE = equiposTerceros[j];
                equiposTerceros[j] = equiposTerceros[j + 1];
                equiposTerceros[j + 1] = tempE;

                int temp;

                temp = puntos[j];
                puntos[j] = puntos[j + 1];
                puntos[j + 1] = temp;

                temp = diferenciaGol[j];
                diferenciaGol[j] = diferenciaGol[j + 1];
                diferenciaGol[j + 1] = temp;

                temp = golesFavor[j];
                golesFavor[j] = golesFavor[j + 1];
                golesFavor[j + 1] = temp;

                char tempC = grupos[j];
                grupos[j] = grupos[j + 1];
                grupos[j + 1] = tempC;
            }
        }
    }
}

void Torneo::seleccionarMejoresTerceros(Equipo **equiposTerceros,
                                        char *gruposTerceros,
                                        Equipo **&mejoresTerceros,
                                        char *&gruposMejores) {

    mejoresTerceros = new Equipo *[8];
    gruposMejores = new char[8];
    memoria += sizeof(Equipo*) * 8;
    memoria += sizeof(char) * 8;
    for (int i = 0; i < 8; i++) {
        iteraciones++;
        mejoresTerceros[i] = equiposTerceros[i];
        gruposMejores[i] = gruposTerceros[i];
    }
}

void Torneo::ordenarSegundos(Equipo **equiposSegundos, int *puntos,
                             int *diferenciaGol, int *golesFavor,
                             char *grupos) {

    for (int i = 0; i < 11; i++) {
        iteraciones++;
        for (int j = 0; j < 11 - i; j++) {
            iteraciones++;
            bool cambiar = false;

            if (puntos[j] < puntos[j + 1])
                cambiar = true;
            else if (puntos[j] == puntos[j + 1] &&
                     diferenciaGol[j] < diferenciaGol[j + 1])
                cambiar = true;
            else if (puntos[j] == puntos[j + 1] &&
                     diferenciaGol[j] == diferenciaGol[j + 1] &&
                     golesFavor[j] < golesFavor[j + 1])
                cambiar = true;

            if (cambiar) {

                Equipo *tempE = equiposSegundos[j];
                equiposSegundos[j] = equiposSegundos[j + 1];
                equiposSegundos[j + 1] = tempE;

                int temp;

                temp = puntos[j];
                puntos[j] = puntos[j + 1];
                puntos[j + 1] = temp;

                temp = diferenciaGol[j];
                diferenciaGol[j] = diferenciaGol[j + 1];
                diferenciaGol[j + 1] = temp;

                temp = golesFavor[j];
                golesFavor[j] = golesFavor[j + 1];
                golesFavor[j + 1] = temp;

                char tempC = grupos[j];
                grupos[j] = grupos[j + 1];
                grupos[j + 1] = tempC;
            }
        }
    }
}

Eliminatoria Torneo::generarDieciseisavos() {

    Equipo **equiposPrimeros;
    Equipo **equiposSegundos;
    Equipo **equiposTerceros;

    char *grupoPrimeros;
    char *grupoSegundos;
    char *grupoTerceros;

    obtenerClasificados(equiposPrimeros, equiposSegundos, equiposTerceros,
                        grupoPrimeros, grupoSegundos, grupoTerceros);

    int puntosT[12], dgT[12], gfT[12];
    int puntosS[12], dgS[12], gfS[12];
    memoria += sizeof(int) * 12 * 6;
    for (int i = 0; i < 12; i++) {
        iteraciones++;
        TablaGrupo tabla(grupos[i]);
        tabla.calcularPuntos();
        tabla.ordenarTabla();

        // terceros
        puntosT[i] = tabla.getPuntos(2);
        dgT[i] = tabla.getDiferenciaGol(2);
        gfT[i] = tabla.getEquipo(2)->getGolesFavor();

        // segundos
        puntosS[i] = tabla.getPuntos(1);
        dgS[i] = tabla.getDiferenciaGol(1);
        gfS[i] = tabla.getEquipo(1)->getGolesFavor();
    }

    ordenarTerceros(equiposTerceros, puntosT, dgT, gfT, grupoTerceros);

    Equipo **mejoresTerceros;
    char *grupoMejoresTerceros;

    seleccionarMejoresTerceros(equiposTerceros, grupoTerceros,
                               mejoresTerceros, grupoMejoresTerceros);

    ordenarSegundos(equiposSegundos, puntosS, dgS, gfS, grupoSegundos);

    Eliminatoria r16;

    r16.crearDesdeClasificados(equiposPrimeros, equiposSegundos,
                               mejoresTerceros,
                               grupoPrimeros, grupoSegundos,
                               grupoMejoresTerceros);
    delete[] equiposPrimeros;
    delete[] equiposSegundos;
    delete[] equiposTerceros;

    delete[] grupoPrimeros;
    delete[] grupoSegundos;
    delete[] grupoTerceros;

    delete[] mejoresTerceros;
    delete[] grupoMejoresTerceros;

    return r16;
}

void contarConf(Equipo **lista, int cant) {

    if (!lista)
        return;

    string confs[50];
    int cont[50] = {0};
    int total = 0;

    for (int i = 0; i < cant; i++) {
        iteraciones++;
        if (!lista[i])
            continue;

        string c = lista[i]->getConfederacion();

        int pos = -1;

        for (int j = 0; j < total; j++) {
            iteraciones++;
            if (confs[j] == c) {
                pos = j;
                break;
            }
        }

        if (pos == -1) {
            confs[total] = c;
            cont[total] = 1;
            total++;
        } else {
            cont[pos]++;
        }
    }

    int max = 0;
    string mejor;

    for (int i = 0; i < total; i++) {
        iteraciones++;
        if (cont[i] > max) {
            max = cont[i];
            mejor = confs[i];
        }
    }

    cout << mejor << " (" << max << ")";
}
void Torneo::mostrarInformeFinal() {

    cout << "\n================ INFORME FINAL ================\n";

    if (!campeon || !campeon[0]) {
        cout << "Primero debes simular el torneo\n";
        return;
    }

    cout << "\nCAMPEON: " << campeon[0]->getPais() << endl;

    cout << "\nTOP 4 DEL MUNDIAL:\n";
    cout << "1. " << campeon[0]->getPais() << endl;

    if (perdedoresFinal && perdedoresFinal[0])
        cout << "2. " << perdedoresFinal[0]->getPais() << endl;

    if (perdedoresSemis) {
        if (perdedoresSemis[0])
            cout << "3. " << perdedoresSemis[0]->getPais() << endl;
        if (perdedoresSemis[1])
            cout << "4. " << perdedoresSemis[1]->getPais() << endl;
    }

    Jugador *maxCampeon = nullptr;
    memoria += sizeof(Jugador*);

    for (int i = 0; i < campeon[0]->getCantidadJugadores(); i++) {
        iteraciones++;
        Jugador *j = campeon[0]->getJugador(i);
        if (!j) continue;

        if (!maxCampeon || j->getEstadistica().getGoles() >
                               maxCampeon->getEstadistica().getGoles()) {
            maxCampeon = j;
        }
    }

    if (maxCampeon) {
        cout << "\nMax goleador del campeon: "
             << maxCampeon->getNombre() << " "
             << maxCampeon->getApellido() << " - "
             << campeon[0]->getPais() << " ("
             << maxCampeon->getEstadistica().getGoles() << ")\n";
    }

    Jugador *top1 = nullptr, *top2 = nullptr, *top3 = nullptr;
    memoria += sizeof(Jugador*) * 3;

    Equipo *eq1 = nullptr, *eq2 = nullptr, *eq3 = nullptr;
    memoria += sizeof(Equipo*) * 3;

    for (int i = 0; i < cantidadEquipos; i++) {
        iteraciones++;
        if (!equipos[i]) continue;

        for (int j = 0; j < equipos[i]->getCantidadJugadores(); j++) {
            iteraciones++;
            Jugador *act = equipos[i]->getJugador(j);
            if (!act) continue;

            int goles = act->getEstadistica().getGoles();

            if (!top1 || goles > top1->getEstadistica().getGoles()) {
                top3 = top2; eq3 = eq2;
                top2 = top1; eq2 = eq1;
                top1 = act;  eq1 = equipos[i];
            } else if (!top2 || goles > top2->getEstadistica().getGoles()) {
                top3 = top2; eq3 = eq2;
                top2 = act;  eq2 = equipos[i];
            } else if (!top3 || goles > top3->getEstadistica().getGoles()) {
                top3 = act;  eq3 = equipos[i];
            }
        }
    }

    cout << "\nTOP 3 GOLEADORES:\n";

    if (top1)
        cout << "1. " << top1->getNombre() << " " << top1->getApellido()
             << " - " << eq1->getPais()
             << " (" << top1->getEstadistica().getGoles() << ")\n";

    if (top2)
        cout << "2. " << top2->getNombre() << " " << top2->getApellido()
             << " - " << eq2->getPais()
             << " (" << top2->getEstadistica().getGoles() << ")\n";

    if (top3)
        cout << "3. " << top3->getNombre() << " " << top3->getApellido()
             << " - " << eq3->getPais()
             << " (" << top3->getEstadistica().getGoles() << ")\n";

    Equipo *maxEquipo = nullptr;
    memoria += sizeof(Equipo*);

    for (int i = 0; i < cantidadEquipos; i++) {
        iteraciones++;
        if (!equipos[i]) continue;

        if (!maxEquipo ||
            equipos[i]->getGolesFavor() > maxEquipo->getGolesFavor()) {
            maxEquipo = equipos[i];
        }
    }

    if (maxEquipo) {
        cout << "\nEquipo con mas goles historicos: "
             << maxEquipo->getPais()
             << " (" << maxEquipo->getGolesFavor() << " goles)\n";
    }

    cout << "\n\nConfederacion con mayor presencia:\n";

    cout << "R16: ";
    contarConf(ganadores16, cant16);
    cout << endl;

    cout << "R8: ";
    contarConf(ganadores8, cant8);
    cout << endl;

    cout << "R4: ";
    contarConf(ganadores4, cant4);
    cout << endl;

    cout << "\n==============================================\n";
}

void Torneo::simularTorneo() {
    if (ganadores16) { delete[] ganadores16; ganadores16 = nullptr; }
    if (ganadores8)  { delete[] ganadores8;  ganadores8  = nullptr; }
    if (ganadores4)  { delete[] ganadores4;  ganadores4  = nullptr; }
    if (ganadores2)  { delete[] ganadores2;  ganadores2  = nullptr; }
    if (campeon)     { delete[] campeon;     campeon     = nullptr; }

    if (perdedoresSemis) { delete[] perdedoresSemis; perdedoresSemis = nullptr; }
    if (perdedoresFinal) { delete[] perdedoresFinal; perdedoresFinal = nullptr; }
    cout << "Inicio simulacion" << endl;

    for (int i = 0; i < cantidadGrupos; i++) {
        iteraciones++;
        grupos[i].generarPartidos();
        memoria += sizeof(Partido) * grupos[i].getCantidadPartidos();
    }

    asignarFechasGrupos();

    for (int g = 0; g < cantidadGrupos; g++) {
        iteraciones++;
        cout << "Partidos grupo " << grupos[g].getLetra() << endl;

        Partido *partidos = grupos[g].getPartidos();
        int cant = grupos[g].getCantidadPartidos();

        for (int i = 0; i < cant; i++) {
            iteraciones++;
            partidos[i].simularPartido();
            partidos[i].mostrarPartido();
        }
        cout << endl;
    }

    mostrarTablasGrupos();
    dieciseisavos = generarDieciseisavos();

    ganadores16 = dieciseisavos.simularRonda(cant16, "DIECISEISAVOS");
    memoria += sizeof(Equipo*) * 32;

    octavos = dieciseisavos.crearSiguienteRonda(ganadores16, cant16);

    ganadores8 = octavos.simularRonda(cant8, "OCTAVOS");
    memoria += sizeof(Equipo*) * 16;

    cuartos = octavos.crearSiguienteRonda(ganadores8, cant8);

    ganadores4 = cuartos.simularRonda(cant4, "CUARTOS");
    memoria += sizeof(Equipo*) * 8;

    semis = cuartos.crearSiguienteRonda(ganadores4, cant4);

    ganadores2 = semis.simularRonda(cant2, "SEMIFINAL");
    memoria += sizeof(Equipo*) * 4;

    perdedoresSemis = new Equipo*[2];
    memoria += sizeof(Equipo*) * 2;

    int idx = 0;

    for (int i = 0; i < cant4; i++) {
        iteraciones++;

        bool esGanador = false;

        for (int j = 0; j < cant2; j++) {
            iteraciones++;
            if (ganadores4[i] == ganadores2[j]) {
                esGanador = true;
                break;
            }
        }

        if (!esGanador && idx < 2) {
            perdedoresSemis[idx++] = ganadores4[i];
        }
    }

    final = semis.crearSiguienteRonda(ganadores2, cant2);

    campeon = final.simularRonda(cant1, "FINAL");
    memoria += sizeof(Equipo*) * 1;

    perdedoresFinal = new Equipo*[1];
    memoria += sizeof(Equipo*) * 1;

    if (ganadores2[0] == campeon[0]) {
        perdedoresFinal[0] = ganadores2[1];
    } else {
        perdedoresFinal[0] = ganadores2[0];
    }
}
