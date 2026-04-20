#include "cargarArchivos.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
string obtenerCampo(const string& linea, int& inicio){
    string campo = "";

    while(inicio < linea.size() && linea[inicio] != ';'){
        campo += linea[inicio];
        inicio++;
    }

    if(inicio < linea.size()) inicio++;

    return campo;
}
string limpiarTexto(const string& texto){
    string resultado = "";

    for(int i = 0; i < texto.size(); i++){
        if(texto[i]!='\r'){
            resultado += texto[i];
        }
    }

    return resultado;
}
int contarLineas(const string nombreArchivo){
    ifstream archivo(nombreArchivo);

    if(!archivo){
        cout << "Error abriendo archivo" << endl;
        return 0;
    }

    string linea;
    int contador = 0;

    while(getline(archivo, linea)){
        linea = limpiarTexto(linea);

        if(linea == "") continue;
        if(!isdigit(linea[0])) continue;

        contador++;
    }

    archivo.close();
    return contador;
}

Equipo* cargarEquipos(const string nombreArchivo, int& cantidadEquipos){
    cantidadEquipos = contarLineas(nombreArchivo);

    ifstream archivo(nombreArchivo);

    if(!archivo){
        cout << "Error abriendo archivo" << endl;
        return nullptr;
    }

    Equipo* equipos = new Equipo[cantidadEquipos];

    string linea;
    getline(archivo, linea);

    int indiceEquipo = 0;
    while(getline(archivo, linea)){
        linea = limpiarTexto(linea);

        if(linea == "") continue;
        if(!isdigit(linea[0])) continue;

        if(indiceEquipo >= cantidadEquipos){
            cout << "Error: demasiadas lineas" << endl;
            break;
        }

        int posicion = 0;

        try{
            int rankingFifa = stoi(obtenerCampo(linea, posicion));
            string nombrePais = obtenerCampo(linea, posicion);
            string directorTecnico = obtenerCampo(linea, posicion);
            string nombreFederacion = obtenerCampo(linea, posicion);
            string nombreConfederacion = obtenerCampo(linea, posicion);

            int golesFavor = stoi(obtenerCampo(linea, posicion));
            int golesContra = stoi(obtenerCampo(linea, posicion));
            int partidosGanados = stoi(obtenerCampo(linea, posicion));
            int partidosEmpatados = stoi(obtenerCampo(linea, posicion));
            int partidosPerdidos = stoi(obtenerCampo(linea, posicion));

            equipos[indiceEquipo].setPais(nombrePais);
            equipos[indiceEquipo].setDirectorTecnico(directorTecnico);
            equipos[indiceEquipo].setConfederacion(nombreConfederacion);
            equipos[indiceEquipo].setFederacion(nombreFederacion);
            equipos[indiceEquipo].setRanking(rankingFifa);

            equipos[indiceEquipo].cargarEstadisticas(
                golesFavor,
                golesContra,
                partidosGanados,
                partidosEmpatados,
                partidosPerdidos
                );

            indiceEquipo++;

        } catch(...){
            cout << "Error en linea: " << linea << endl;
        }
    }

    archivo.close();
    return equipos;
}
