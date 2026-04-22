#include "torneo.h"
#include "equipo.h"
#include "InicializarDatos.h"
#include "cargarArchivos.h"

using namespace std;

int main(){

    int cantidad;
    Equipo* equiposPlano = cargarEquipos("selecciones_clasificadas_mundial.csv", cantidad);

    Equipo** equipos = new Equipo*[cantidad];

    for(int i = 0; i < cantidad; i++){
        equipos[i] = &equiposPlano[i];
    }

    Torneo torneo;

    torneo.setEquipos(equipos, cantidad);
    torneo.inicializarGrupos(12);

    torneo.simularTorneo();
    torneo.mostrarGrupos();
    torneo.mostrarBombos();
    inicializarJugadoresEquipos(equiposPlano,cantidad);
    imprimirJugadoresEquipos(equiposPlano, cantidad);
    guardarJugadoresCSV("jugadores.csv", equiposPlano,cantidad);
    copiarArchivoCSV("selecciones_clasificadas_mundial.csv", "post_mundial.csv");

    return 0;
}
