#include <iostream>
#include "cargarArchivos.h"
using namespace std;

int main(){

    int cantidadEquipos;
    Equipo* equipos = cargarEquipos("selecciones_clasificadas_mundial.csv", cantidadEquipos);

    cout << equipos[5].getDirectorTecnico() << endl;

    delete[] equipos;

    return 0;
}
