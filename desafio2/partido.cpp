#include "partido.h"
#include "equipo.h"
#include "jugador.h"
#include <cmath>
#include <iostream>
#include <random>
using namespace std;
static mt19937 gen(std::random_device{}());

Partido::Partido() {
    equipo1 = NULL;
    equipo2 = NULL;

    golesEquipo1 = 0;
    golesEquipo2 = 0;

    cantidadConvocados = 11;

    convocadosEquipo1 = new Jugador *[11];
    convocadosEquipo2 = new Jugador *[11];
}

Partido::Partido(const Partido &copia) {
    fecha = copia.fecha;
    hora = copia.hora;
    sede = copia.sede;

    for (int i = 0; i < 3; i++)
        arbitros[i] = copia.arbitros[i];

    equipo1 = copia.equipo1;
    equipo2 = copia.equipo2;

    cantidadConvocados = copia.cantidadConvocados;

    convocadosEquipo1 = new Jugador*[11];
    convocadosEquipo2 = new Jugador*[11];

    for (int i = 0; i < 11; i++) {
        convocadosEquipo1[i] = copia.convocadosEquipo1[i];
        convocadosEquipo2[i] = copia.convocadosEquipo2[i];
    }
}

Partido::~Partido() {
    delete[] convocadosEquipo1;
    delete[] convocadosEquipo2;
}

Equipo *Partido::getEquipo1() { return equipo1; }
Equipo *Partido::getEquipo2() { return equipo2; }
string Partido::getFecha() { return fecha; }
string Partido::getHora() { return hora; }
string Partido::getSede() { return sede; }
int Partido::getGolesEquipo1() { return golesEquipo1; }
int Partido::getGolesEquipo2() { return golesEquipo2; }
Jugador **Partido::getConvocadosEquipo1() { return convocadosEquipo1;}
Jugador **Partido::getConvocadosEquipo2() {return convocadosEquipo2;}
string Partido::getArbitro(int i) {
    if (i >= 0 && i < 3)
        return arbitros[i];
    return "";
}

void Partido::setEquipos(Equipo *equipo1, Equipo *equipo2) {
    this->equipo1 = equipo1;
    this->equipo2 = equipo2;
}

void Partido::setHora(const string &hora) { this->hora = hora; }

void Partido::setSede(const string &sede) { this->sede = sede; }

void Partido::setArbitros(const string arbitros[3]) {
    for (int i = 0; i < 3; i++)
        this->arbitros[i] = arbitros[i];
}

void Partido::setFecha(const string &fecha) { this->fecha = fecha; }
float Partido::calcularLambda(float gf, float gc) {
    float mu = 1.35f;
    float alpha = 0.6f;
    float beta = 0.4f;

    return mu * pow(gf / mu, alpha) * pow(gc / mu, beta);
}
int Partido::generarPoisson(float lambda) {

    uniform_real_distribution<> dist(0.0, 1.0);

    float L = exp(-lambda);
    float p = 1.0;
    int k = 0;

    do {
        k++;
        p *= dist(gen);
    } while (p > L);

    return k - 1;
}
void Partido::calcularPosesion() {

    int r1 = equipo1->getRanking();
    int r2 = equipo2->getRanking();

    float inv1 = 1.0f / r1;
    float inv2 = 1.0f / r2;

    float total = inv1 + inv2;

    posesionEquipo1 = (inv1 / total) * 100;
    posesionEquipo2 = (inv2 / total) * 100;
}
void Partido::convocarJugadores() {

    bool usados1[26] = {false};
    bool usados2[26] = {false};

    for (int i = 0; i < 11;) {

        uniform_int_distribution<> dist(0, equipo1->getCantidadJugadores() - 1);
        int idx = dist(gen);

        if (!usados1[idx]) {
            convocadosEquipo1[i] = equipo1->getJugador(idx);
            usados1[idx] = true;
            i++;
        }
    }

    for (int i = 0; i < 11;) {

        uniform_int_distribution<> dist(0, equipo2->getCantidadJugadores() - 1);
        int idx = dist(gen);

        if (!usados2[idx]) {
            convocadosEquipo2[i] = equipo2->getJugador(idx);
            usados2[idx] = true;
            i++;
        }
    }
}
void Partido::simularEventos(Jugador **jugadores, int golesEquipo,int *goleadores, int &cantGoleadores,const string &nombreEquipo) {
    uniform_real_distribution<> dist(0.0, 1.0);

    for (int i = 0; i < 11; i++) {

        int amarillas = 0;

        float r = dist(gen);
        if (r < 0.06)
            amarillas++;

        r = dist(gen);
        if (amarillas == 1 && r < 0.0115)
            amarillas++;

        int rojas = (amarillas == 2) ? 1 : 0;

        int faltas = 0;

        r = dist(gen);
        if (r < 0.13)
            faltas++;

        r = dist(gen);
        if (faltas == 1 && r < 0.0275)
            faltas++;

        r = dist(gen);
        if (faltas == 2 && r < 0.007)
            faltas++;

        jugadores[i]->actualizarEstadisticas(0, 90, amarillas, rojas, faltas);

        if (amarillas > 0) {
            cout << "Amarilla - " << nombreEquipo << " jugador #"
                 << jugadores[i]->getNumero() << endl;
        }

        if (rojas > 0) {
            cout << "Roja - " << nombreEquipo << " jugador #"
                 << jugadores[i]->getNumero() << endl;
        }
    }

    int golesAsignados = 0;

    while (golesAsignados < golesEquipo) {

        for (int i = 0; i < 11 && golesAsignados < golesEquipo; i++) {

            float r = dist(gen);

            if (r < 0.04) {

                jugadores[i]->actualizarEstadisticas(1, 0, 0, 0, 0);

                goleadores[cantGoleadores++] = jugadores[i]->getNumero();

                golesAsignados++;
            }
        }
    }
}
void Partido::actualizarEquipos() {

    int res1, res2;

    if (golesEquipo1 > golesEquipo2) {
        res1 = 1;
        res2 = -1;
    } else if (golesEquipo1 < golesEquipo2) {
        res1 = -1;
        res2 = 1;
    } else {
        res1 = 0;
        res2 = 0;
    }

    equipo1->actualizarEstadisticas(golesEquipo1, golesEquipo2, res1);
    equipo2->actualizarEstadisticas(golesEquipo2, golesEquipo1, res2);
}
void Partido::simularPartido() {

    convocarJugadores();

    float lambda1 = calcularLambda(equipo1->getPromedioGolesFavor(),
                                   equipo2->getPromedioGolesContra());

    float lambda2 = calcularLambda(equipo2->getPromedioGolesFavor(),
                                   equipo1->getPromedioGolesContra());

    golesEquipo1 = generarPoisson(lambda1);
    golesEquipo2 = generarPoisson(lambda2);

    cantGoleadores1 = 0;
    cantGoleadores2 = 0;

    simularEventos(convocadosEquipo1, golesEquipo1, goleadoresEquipo1,
                   cantGoleadores1, equipo1->getPais());
    simularEventos(convocadosEquipo2, golesEquipo2, goleadoresEquipo2,
                   cantGoleadores2, equipo2->getPais());

    calcularPosesion();

    actualizarEquipos();
    for (int i = 0; i < 11; i++) {
        convocadosEquipo1[i]->sumarPartido();
        convocadosEquipo2[i]->sumarPartido();
    }
}
void Partido::mostrarPartido() {

    cout << "----------------------------------------\n";
    cout << fecha << " | " << hora << endl;
    cout << "Sede: " << sede << endl;
    cout << "Arbitros: " << arbitros[0] << ", "
         << arbitros[1] << ", " << arbitros[2] << endl;

    cout << equipo1->getPais() << " " << golesEquipo1
         << " - " << golesEquipo2 << " "
         << equipo2->getPais() << endl;

    cout << "Posesion: " << equipo1->getPais() << " "
         << posesionEquipo1 << "% | "
         << equipo2->getPais() << " "
         << posesionEquipo2 << "%" << endl;

    cout << "Goleadores " << equipo1->getPais() << ": ";
    for (int i = 0; i < cantGoleadores1; i++) {
        cout << goleadoresEquipo1[i] << " ";
    }
    cout << endl;

    cout << "Goleadores " << equipo2->getPais() << ": ";
    for (int i = 0; i < cantGoleadores2; i++) {
        cout << goleadoresEquipo2[i] << " ";
    }
    cout << endl;

    cout << "----------------------------------------\n\n";
}

void Partido::setGoles(int g1, int g2) {
    golesEquipo1 = g1;
    golesEquipo2 = g2;
}

Partido &Partido::operator=(const Partido &otro) {

    if (this != &otro) {

        delete[] convocadosEquipo1;
        delete[] convocadosEquipo2;

        equipo1 = otro.equipo1;
        equipo2 = otro.equipo2;
        fecha = otro.fecha;
        hora = otro.hora;
        sede = otro.sede;

        for (int i = 0; i < 3; i++)
            arbitros[i] = otro.arbitros[i];

        cantidadConvocados = otro.cantidadConvocados;

        convocadosEquipo1 = new Jugador*[11];
        convocadosEquipo2 = new Jugador*[11];

        for (int i = 0; i < 11; i++) {
            convocadosEquipo1[i] = otro.convocadosEquipo1[i];
            convocadosEquipo2[i] = otro.convocadosEquipo2[i];
        }
    }

    return *this;
}
