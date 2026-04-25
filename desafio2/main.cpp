#include "InicializarDatos.h"
#include "equipo.h"
#include "jugador.h"
#include "torneo.h"
#include "cargarArchivos.h"
#include "iostream"
using namespace std;
long long iteraciones = 0;
long long memoria = 0;
int main() {
    int cantidad;
    Equipo *equiposPlano =cargarEquipos("selecciones_clasificadas_mundial.csv", cantidad);
    iteraciones++;

    Equipo **equipos = new Equipo *[cantidad];
    iteraciones++;
    memoria += sizeof(Equipo*) * cantidad;

    for (int i = 0; i < cantidad; i++) {
        iteraciones++;
        equipos[i] = &equiposPlano[i];
    }
    inicializarJugadoresEquipos(equiposPlano, cantidad);
    iteraciones++;
    memoria += sizeof(Jugador) * 26 * cantidad;

    cout << "\n--- CARGA DE DATOS ---" << endl<<"Iteraciones: " << iteraciones << endl << "Memoria usada: " << memoria << " bytes" << endl<<"\n--- SORTEO DE GRUPOS ----"<<endl;
    long long memoria1=memoria;
    long long iteraciones1=iteraciones;

    memoria=0;
    iteraciones = 0;
    Torneo torneo;
    memoria += sizeof(Torneo);
    torneo.setEquipos(equipos, cantidad);
    torneo.inicializarGrupos(12);
    torneo.realizarSorteo();
    torneo.mostrarBombos();
    torneo.mostrarGrupos();

    cout << endl<<"Iteraciones: " << iteraciones << endl << "Memoria usada: " << memoria << " bytes" << endl<<"======================================================"<<endl<<endl;
    long long memoria2=memoria;
    long long iteraciones2=iteraciones;
    memoria=0;
    iteraciones=0;
    torneo.simularTorneo();
    cout << endl<<"Iteraciones: " << iteraciones << endl << "Memoria usada: " << memoria << " bytes" << endl<<"======================================================"<<endl<<endl;

    long long memoria3=memoria;
    long long iteraciones3=iteraciones;
    guardarEquiposCSV("equipos_post.csv", equiposPlano, cantidad);
    guardarJugadoresCSV("jugadores_post.csv", equiposPlano, cantidad);

    delete[] equipos;
    delete[] equiposPlano;
    cout<<"Memoria total usada en el programa es: "<<memoria1+memoria2+memoria3<<endl<<"iteraciones totales en el programa: "<<iteraciones1+iteraciones2+iteraciones3<<endl;
    return 0;

}
