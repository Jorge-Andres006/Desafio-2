#ifndef TORNEO_H
#define TORNEO_H
#include <string>
using namespace std;
class Equipo;
class Grupo;
class Partido;
class Eliminatoria;

class Torneo{
private:
    string nombre;
    string fechaInicio;
    int anio;

    Equipo** equipos;
    int cantidadEquipos;

    Grupo* grupos;
    int cantidadGrupos;

    Equipo** bombo1;
    Equipo** bombo2;
    Equipo** bombo3;
    Equipo** bombo4;

    void ordenarPorRanking();
    void conformarBombos();
    bool sorteo();
    int sortearDeBombo(Equipo** bombo, bool* usado, int tamano, Grupo& grupo);
    bool esValido(Grupo& grupo, Equipo* equipo);
    void asignarFechasGrupos();

public:
    Torneo();
    Torneo(const Torneo& otro);
    ~Torneo();

    Torneo& operator=(const Torneo& otro);

    void setEquipos(Equipo** equipos, int cantidad);
    void inicializarGrupos(int cantidad);

    void realizarSorteo();
    void simularTorneo();

    void mostrarGrupos();
    void mostrarTablasGrupos();
    void mostrarBombos();

    Grupo* getGrupos();
    int getCantidadGrupos();

    void obtenerClasificados(
        Equipo**& equiposPrimeros,
        Equipo**& equiposSegundos,
        Equipo**& equiposTerceros,
        char*& grupoPrimeros,
        char*& grupoSegundos,
        char*& grupoTerceros
        );

    void ordenarTerceros(
        Equipo** equiposTerceros,
        int* puntos,
        int* diferenciaGol,
        int* golesFavor,
        char* grupos
        );

    void seleccionarMejoresTerceros(
        Equipo** equiposTerceros,
        char* gruposTerceros,
        Equipo**& mejoresTerceros,
        char*& gruposMejores
        );

    void ordenarSegundos(
        Equipo** equiposSegundos,
        int* puntos,
        int* diferenciaGol,
        int* golesFavor,
        char* grupos
        );

   Eliminatoria generarDieciseisavos();
};

#endif
