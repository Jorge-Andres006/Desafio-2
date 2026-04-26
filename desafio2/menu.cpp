#include "menu.h"
#include "InicializarDatos.h"
#include "equipo.h"
#include "jugador.h"
#include "torneo.h"
#include "cargarArchivos.h"
#include <iostream>
using namespace std;

extern long long iteraciones;
extern long long memoria;
int leerEntero() {
    int valor;

    while (true) {
        cin >> valor;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Ingresa un numero: ";
        } else {
            cin.ignore(10000, '\n');
            return valor;
        }
    }
}
void ejecutarMenu() {

    int opcion;

    int cantidad = 0;
    Equipo *equiposPlano = nullptr;
    Equipo **equipos = nullptr;

    Torneo torneo;

    long long memoria1 = 0, memoria2 = 0, memoria3 = 0, memoria4=0, memoria5=0;
    long long iteraciones1 = 0, iteraciones2 = 0, iteraciones3 = 0, iteraciones4=0, iteraciones5=0;

    do {
        cout << "\n====== MENU ======\n";
        cout << "1. Cargar datos e inicializar datos\n";
        cout << "2. Realizar sorteo\n";
        cout << "3. Simular torneo\n";
        cout << "4. Guardar resultados\n";
        cout << "5. Ver informe final\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        opcion = leerEntero();

        switch (opcion) {

        case 1: {
            memoria = 0;
            iteraciones = 0;

            if (equipos) {
                delete[] equipos;
                equipos = nullptr;
            }

            if (equiposPlano) {
                delete[] equiposPlano;
                equiposPlano = nullptr;
            }

            equiposPlano = cargarEquipos("selecciones_clasificadas_mundial.csv", cantidad);
            iteraciones++;

            equipos = new Equipo *[cantidad];
            memoria += sizeof(Equipo*) * cantidad;

            for (int i = 0; i < cantidad; i++) {
                iteraciones++;
                equipos[i] = &equiposPlano[i];
            }

            inicializarJugadoresEquipos(equiposPlano, cantidad);
            memoria += sizeof(Jugador) * 26 * cantidad;

            cout << "\n--- CARGA DE DATOS ---\n";
            cout << "Iteraciones: " << iteraciones << endl;
            cout << "Memoria usada: " << memoria << " bytes\n";

            memoria1 = memoria;
            iteraciones1 = iteraciones;
            break;
        }

        case 2: {
            if (!equipos) {
                cout << "Primero carga los datos\n";
                break;
            }

            memoria = 0;
            iteraciones = 0;

            memoria += sizeof(Torneo);

            torneo.setEquipos(equipos, cantidad);
            torneo.inicializarGrupos(12);
            torneo.realizarSorteo();

            torneo.mostrarBombos();
            torneo.mostrarGrupos();

            cout << "\n--- SORTEO ---\n";
            cout << "Iteraciones: " << iteraciones << endl;
            cout << "Memoria usada: " << memoria << " bytes\n";

            memoria2 = memoria;
            iteraciones2 = iteraciones;
            break;
        }

        case 3: {
            if (torneo.getCantidadGrupos() == 0) {
                cout << "Primero realiza el sorteo\n";
                break;
            }

            memoria = 0;
            iteraciones = 0;

            torneo.simularTorneo();

            cout << "\n--- SIMULACION ---\n";
            cout << "Iteraciones: " << iteraciones << endl;
            cout << "Memoria usada: " << memoria << " bytes\n";

            memoria3= memoria;
            iteraciones3 = iteraciones;
            break;
        }

        case 4: {
            if (!equiposPlano) {
                cout << "Primero debes cargar los datos\n";
                break;
            }

            if (torneo.getCantidadGrupos() == 0) {
                cout << "Primero debes realizar el sorteo\n";
                break;
            }

            if (memoria3==0) {
                cout << "Primero debes simular el torneo\n";
                break;
            }

            memoria = 0;
            iteraciones = 0;

            guardarEquiposCSV("equipos_post.csv", equiposPlano, cantidad);
            guardarJugadoresCSV("jugadores_post.csv", equiposPlano, cantidad);

            cout << "\n--- GUARDADO ---\n";
            cout << "Iteraciones: " << iteraciones << endl;
            cout << "Memoria usada: " << memoria << " bytes\n";

            memoria4 = memoria;
            iteraciones4 = iteraciones;

            break;
        }

        case 5: {
            if (!equipos || torneo.getCantidadGrupos() == 0) {
                cout << "Primero carga, sortea y simula el torneo\n";
                break;
            }

            memoria = 0;
            iteraciones = 0;

            torneo.mostrarInformeFinal();

            cout << "\n--- INFORME FINAL ---\n";
            cout << "Iteraciones: " << iteraciones << endl;
            cout << "Memoria usada: " << memoria << " bytes\n";

            memoria5= memoria;
            iteraciones5 = iteraciones;

            break;
        }

        case 0:
            cout << "\nSaliendo...\n";
            cout << "Memoria total usada: "
                 << memoria1 + memoria2 + memoria3 +memoria4+memoria5<< endl;
            cout << "Iteraciones totales: "
                 << iteraciones1 + iteraciones2 + iteraciones3+iteraciones4+iteraciones5 << endl;
            break;

        default:
            cout << "Opcion invalida\n";
        }

    } while (opcion != 0);

    if (equipos) delete[] equipos;
    if (equiposPlano) delete[] equiposPlano;
}

