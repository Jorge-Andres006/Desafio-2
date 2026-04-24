#ifndef ESTADISTICAJUGADOR_H
#define ESTADISTICAJUGADOR_H

class EstadisticaJugador {
private:
    int partidosJugados;
    int goles;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;
    int minutosJugados;

public:
    // Constructores
    EstadisticaJugador();
    EstadisticaJugador(const EstadisticaJugador &copia); // constructor copia

    // Destructor
    ~EstadisticaJugador();

    // Getters
    int getPartidosJugados();
    int getGoles();
    int getMinutosJugados();
    int getAsistencias();
    int getTarjetasAmarillas();
    int getTarjetasRojas();
    int getFaltas();

    // Setters
    void setPartidosJugados(int pj);
    void setGoles(int g);
    void setMinutosJugados(int mj);
    void setAsistencias(int a);
    void setTarjetasAmarillas(int ta);
    void setTarjetasRojas(int tr);
    void setFaltas(int f);

    // Operaciones principales
    void actualizar(int goles, int minutos, int amarillas, int rojas, int faltas);
    void sumarPartido();

    // Despliegue
    void mostrar();

    // Sobrecarga de operador
    EstadisticaJugador &operator=(const EstadisticaJugador &otro);
};

#endif // ESTADISTICAJUGADOR_H
