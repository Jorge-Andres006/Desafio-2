#ifndef EQUIPO_H
#define EQUIPO_H
#include <string>
using namespace std;
class Jugador;

class Equipo{
private:
    string pais;
    string confederacion;
    string federacion;
    string directorTecnico;

    int ranking;
    int puntos;

    int golesFavor;
    int golesContra;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;

    Jugador* jugadores;
    int cantidadJugadores;

public:
    //constructores
    Equipo();
    Equipo(const Equipo& copia);

    //destructor
    ~Equipo();

    //getters
    string getPais();
    int getRanking();
    int getPuntos();
    string getConfederacion();
    string getDirectorTecnico();

    //setters
    void setPais(const string& pais);
    void setConfederacion(const string& confederacion);
    void setDirectorTecnico(const string& dt);
    void setRanking(int ranking);
    void setFederacion(const string& federacion);

    //metodos principales
    void agregarJugador(const Jugador& jugador);
    void actualizarEstadisticas(int golesfavor,int golesContra,int amarallis, int rojas, int faltas, int resultadoPartido);

    //despliegue
    void mostrarEquipo();

    //sobrecarga
    Equipo& operator=(const Equipo& otro);

};

#endif // EQUIPO_H
