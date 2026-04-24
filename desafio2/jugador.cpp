#include "jugador.h"
#include "estadisticajugador.h"
#include <iostream>
using namespace std;

Jugador::Jugador() {
    nombre = "";
    apellido = "";
    numero = 0;
    estadisticas = EstadisticaJugador();
}

Jugador::Jugador(const Jugador &copia) {
    nombre = copia.nombre;
    apellido = copia.apellido;
    numero = copia.numero;
    estadisticas = copia.estadisticas;
}

Jugador::~Jugador() {}

string Jugador::getNombre() { return nombre; }

string Jugador::getApellido() { return apellido; }

int Jugador::getNumero() { return numero; }

int Jugador::getGoles() { return estadisticas.getGoles(); }
int Jugador::getMinutos() { return estadisticas.getMinutosJugados(); }

int Jugador::getAmarillas() { return estadisticas.getTarjetasAmarillas(); }

int Jugador::getRojas() { return estadisticas.getTarjetasRojas(); }

int Jugador::getFaltas() { return estadisticas.getFaltas(); }

int Jugador::getAsistencias() { return estadisticas.getAsistencias(); }

int Jugador::getPartidos() { return estadisticas.getPartidosJugados(); }

EstadisticaJugador &Jugador::getEstadistica() { return estadisticas; }
// setters
void Jugador::setNombre(const string nombre) { this->nombre = nombre; }

void Jugador::setApellido(const string apellido) { this->apellido = apellido; }

void Jugador::setNumero(int numero) { this->numero = numero; }
void Jugador::sumarPartido() { estadisticas.sumarPartido(); }
void Jugador::actualizarEstadisticas(int goles, int minutos, int amarillas,
                                     int rojas, int faltas) {
    estadisticas.actualizar(goles, minutos, amarillas, rojas, faltas);
}

void Jugador::mostrarJugador() {
    cout << "Nombre: " << nombre << " " << apellido << endl;
    cout << "Numero: " << numero << endl;
    estadisticas.mostrar();
}

Jugador &Jugador::operator=(const Jugador &otro) {
    if (this != &otro) {
        nombre = otro.nombre;
        apellido = otro.apellido;
        numero = otro.numero;
        estadisticas = otro.estadisticas;
    }
    return *this;
}
