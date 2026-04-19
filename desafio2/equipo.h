#ifndef EQUIPO_H
#define EQUIPO_H
class Jugador;

class Equipo{
private:
    char* pais;
    char* confederacion;
    char* directorTecnico;

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
    char* getPais();
    int getRanking();
    int getPuntos();
    char* getConfederacion();

    //setters
    void setPais(const char* pais);
    void setConfederacion(const char* confederacion);
    void setDirectorTecnico(const char* dt);
    void setRanking(int ranking);

    //metodos principales
    void agregarJugador(const Jugador& jugador);
    void actualizarEstadisticas(int golesfavor,int golesContra,int amarallis, int rojas, int faltas, int resultadoPartido);

    //despliegue
    void mostrarEquipo();

    //sobrecarga
    Equipo& operator=(const Equipo& otro);

};

#endif // EQUIPO_H
