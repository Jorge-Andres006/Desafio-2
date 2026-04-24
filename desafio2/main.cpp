#include "InicializarDatos.h"
#include "eliminatoria.h"
#include "equipo.h"
#include "torneo.h"
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
    torneo.mostrarTablasGrupos();

    Eliminatoria dieciseisavos = torneo.generarDieciseisavos();

    int cant16;
    Equipo **ganadores16 = dieciseisavos.simularRonda(cant16, "DIECISEISAVOS");

    Eliminatoria octavos = dieciseisavos.crearSiguienteRonda(ganadores16, cant16);

    int cant8;
    Equipo **ganadores8 = octavos.simularRonda(cant8, "OCTAVOS");

    Eliminatoria cuartos = octavos.crearSiguienteRonda(ganadores8, cant8);

    int cant4;
    Equipo **ganadores4 = cuartos.simularRonda(cant4, "CUARTOS");

    Eliminatoria semis = cuartos.crearSiguienteRonda(ganadores4, cant4);

    int cant2;
    Equipo **ganadores2 = semis.simularRonda(cant2, "SEMIFINAL");

    Equipo **perdedoresSemis = new Equipo *[2];
    int idx = 0;

    for (int i = 0; i < cant4; i++) {

        bool esGanador = false;

        for (int j = 0; j < cant2; j++) {
            if (ganadores4[i] == ganadores2[j]) {
                esGanador = true;
                break;
            }
        }

        if (!esGanador && idx < 2) {
            perdedoresSemis[idx++] = ganadores4[i];
        }
    }

    Eliminatoria final = semis.crearSiguienteRonda(ganadores2, cant2);

    int cant1;
    Equipo **campeon = final.simularRonda(cant1, "FINAL");

    Equipo **perdedoresFinal = new Equipo *[1];
    perdedoresFinal[0] =
        (ganadores2[0] == campeon[0]) ? ganadores2[1] : ganadores2[0];

    torneo.mostrarInformeFinal(equipos, cantidad, campeon, perdedoresFinal,
                               perdedoresSemis, ganadores16, cant16, ganadores8,
                               cant8, ganadores4, cant4);


    return 0;
}
