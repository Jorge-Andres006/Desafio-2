#include "equipo.h"
#include "cargarArchivos.h"
#include "jugador.h"
#include <iostream>
using namespace std;
//constructor
Equipo::Equipo() {
    pais = "";
    confederacion = "";
    federacion = "";
    directorTecnico = "";
    ranking = 0;
    estadisticas = EstadisticaEquipo();
    jugadores = nullptr;
    cantidadJugadores = 0;
}
//constructor de copia
Equipo::Equipo(const Equipo &copia) {
    pais = copia.pais;
    confederacion = copia.confederacion;
    federacion = copia.federacion;
    directorTecnico = copia.directorTecnico;
    ranking = copia.ranking;
    estadisticas = copia.estadisticas;

    cantidadJugadores = copia.cantidadJugadores;

    if (cantidadJugadores > 0) {
        jugadores = new Jugador[cantidadJugadores];
        memoria += sizeof(Jugador) * cantidadJugadores;
        for (int i = 0; i < cantidadJugadores; i++) {
            iteraciones++;
            jugadores[i] = copia.jugadores[i];
        }
    } else {
        jugadores = nullptr;
    }
}
//destructor
Equipo::~Equipo() { delete[] jugadores; }

// getters
string Equipo::getPais() const {
    return pais;
}
int Equipo::getRanking() const {
    return ranking;
}
string Equipo::getDirectorTecnico() const {
    return directorTecnico;
}
string Equipo::getConfederacion() const {
    return confederacion;
}
Jugador* Equipo::getJugador(int indice) const {
    if (jugadores == nullptr) return nullptr;

    if (indice >= 0 && indice < cantidadJugadores) {
        return &jugadores[indice];
    }
    return nullptr;
}

int Equipo::getCantidadJugadores() const { return cantidadJugadores; }
string Equipo::getFederacion() const { return federacion; }

// setters
void Equipo::setPais(const string &pais) { this->pais = pais; }
void Equipo::setConfederacion(const string &confederacion) {
    this->confederacion = confederacion;
}
void Equipo::setDirectorTecnico(const string &dt) {
    this->directorTecnico = dt;
}
void Equipo::setRanking(int ranking) { this->ranking = ranking; }
void Equipo::setFederacion(const string &federacion) {
    this->federacion = federacion;
}

// metodos
void Equipo::agregarJugador(const Jugador &jugador) {
    Jugador *nuevo = new Jugador[cantidadJugadores + 1];
    for (int i = 0; i < cantidadJugadores; i++) {
        iteraciones++;
        nuevo[i] = jugadores[i];
    }

    nuevo[cantidadJugadores] = jugador;

    delete[] jugadores;
    jugadores = nuevo;
    cantidadJugadores++;
}

void Equipo::actualizarEstadisticas(int golesFavor, int golesContra,
                                    int resultado) {
    estadisticas.actualizar(golesFavor, golesContra, resultado);
}

void Equipo::cargarEstadisticas(int golesFavor, int golesContra,
                                int partidosGanados, int partidosEmpatados,
                                int partidosPerdidos) {
    estadisticas.setGolesFavor(golesFavor);
    estadisticas.setGolesContra(golesContra);
    estadisticas.setPartidosGanados(partidosGanados);
    estadisticas.setPartidosEmpatados(partidosEmpatados);
    estadisticas.setPartidosPerdidos(partidosPerdidos);
}

void Equipo::mostrarEquipo() {
    cout << "Direccion en memoria: " << this << endl;
    cout << "Pais: " << pais << endl;
    cout << "Ranking: " << ranking << endl;
    cout << "Confederacion: " << confederacion << endl;
    cout << "Director Tecnico: " << directorTecnico << endl;
    estadisticas.mostrar();
}
float Equipo::getPromedioGolesFavor() {

    int partidosJugados = estadisticas.getPartidosGanados() +
                          estadisticas.getPartidosEmpatados() +
                          estadisticas.getPartidosPerdidos();

    if (partidosJugados == 0)
        return 1.0;

    return (float)estadisticas.getGolesFavor() / partidosJugados;
}

float Equipo::getPromedioGolesContra() {

    int partidosJugados = estadisticas.getPartidosGanados() +
                          estadisticas.getPartidosEmpatados() +
                          estadisticas.getPartidosPerdidos();

    if (partidosJugados == 0)
        return 1.0;

    return (float)estadisticas.getGolesContra() / partidosJugados;
}
Equipo &Equipo::operator=(const Equipo &otro) {
    if (this != &otro) {
        pais = otro.pais;
        confederacion = otro.confederacion;
        federacion = otro.federacion;
        directorTecnico = otro.directorTecnico;
        ranking = otro.ranking;
        estadisticas = otro.estadisticas;

        delete[] jugadores;

        cantidadJugadores = otro.cantidadJugadores;

        if (cantidadJugadores > 0) {
            jugadores = new Jugador[cantidadJugadores];
            memoria += sizeof(Jugador) * cantidadJugadores;
            for (int i = 0; i < cantidadJugadores; i++) {
                iteraciones++;
                jugadores[i] = otro.jugadores[i];
            }
        } else {
            jugadores = nullptr;
        }
    }

    return *this;
}

int Equipo::getGolesFavor() { return estadisticas.getGolesFavor(); }

EstadisticaEquipo &Equipo::getEstadistica() { return estadisticas; }
