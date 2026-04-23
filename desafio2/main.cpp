#include "torneo.h"
#include "equipo.h"
#include "InicializarDatos.h"
#include "eliminatoria.h"
#include <iostream>

using namespace std;

int main(){

    int cantidad;
    Equipo* equiposPlano = cargarEquipos("selecciones_clasificadas_mundial.csv", cantidad);

    Equipo** equipos = new Equipo*[cantidad];

    for(int i = 0; i < cantidad; i++){
        equipos[i] = &equiposPlano[i];
    }

    inicializarJugadoresEquipos(equiposPlano, cantidad);

    Torneo torneo;

    torneo.setEquipos(equipos, cantidad);
    torneo.inicializarGrupos(12);
    torneo.realizarSorteo();
    torneo.mostrarGrupos();
    torneo.simularTorneo();
    torneo.mostrarTablasGrupos();
    Eliminatoria dieciseisavos = torneo.generarDieciseisavos();

    int cant16;
    Equipo** ganadores16 = dieciseisavos.simularRonda(cant16, "DIECISEISAVOS");

    // cout << "Ganadores16: " << cant16 << endl;

    // for(int i = 0; i < cant16; i++){
    //     if(ganadores16[i] == nullptr){
    //         cout << "NULL en posicion " << i << endl;
    //     }else{
    //         cout << ganadores16[i]->getPais() << endl;
    //     }
    // }

    // OCTAVOS
    Eliminatoria octavos = dieciseisavos.crearSiguienteRonda(ganadores16, cant16);

    int cant8;
    Equipo** ganadores8 = octavos.simularRonda(cant8, "OCTAVOS");

    // CUARTOS
    Eliminatoria cuartos = octavos.crearSiguienteRonda(ganadores8, cant8);

    int cant4;
    Equipo** ganadores4 = cuartos.simularRonda(cant4, "CUARTOS");

    // SEMIFINAL
    Eliminatoria semis = cuartos.crearSiguienteRonda(ganadores4, cant4);

    int cant2;
    Equipo** ganadores2 = semis.simularRonda(cant2, "SEMIFINAL");

    // FINAL
    Eliminatoria final = semis.crearSiguienteRonda(ganadores2, cant2);

    int cant1;
    Equipo** campeon = final.simularRonda(cant1, "FINAL");

    cout << "\n====== CAMPEON ======\n";
    cout << campeon[0]->getPais() << endl;

    return 0;
}
