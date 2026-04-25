#include "InicializarDatos.h"
#include "equipo.h"
#include "torneo.h"
#include "cargarArchivos.h"
using namespace std;

int main() {

    int cantidad;
    Equipo *equiposPlano =
        cargarEquipos("selecciones_clasificadas_mundial.csv", cantidad);

    Equipo **equipos = new Equipo *[cantidad];
    for (int i = 0; i < cantidad; i++) {
        equipos[i] = &equiposPlano[i];
    }

    inicializarJugadoresEquipos(equiposPlano, cantidad);

    Torneo torneo;
    torneo.setEquipos(equipos, cantidad);
    torneo.inicializarGrupos(12);
    torneo.realizarSorteo();
    torneo.mostrarBombos();
    torneo.mostrarGrupos();
    torneo.simularTorneo();

    guardarEquiposCSV("equipos_post.csv", equiposPlano, cantidad);
    guardarJugadoresCSV("jugadores_post.csv", equiposPlano, cantidad);
    return 0;
}
