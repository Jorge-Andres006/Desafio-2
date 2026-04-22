#ifndef ESTADISTICAJUGADOR_H
#define ESTADISTICAJUGADOR_H

class EstadisticaJugador{
private:
    int partidosJugados;
    int goles;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;
    int minutosJugados;

public:
    EstadisticaJugador();
    EstadisticaJugador(const EstadisticaJugador& copia);
    ~EstadisticaJugador();

    int getPartidosJugados();
    int getGoles();
    int getMinutosJugados();
    int getAsistencias();
    int getTarjetasAmarillas();
    int getTarjetasRojas();
    int getFaltas();

    void setPartidosJugados(int pj);
    void setGoles(int g);
    void setMinutosJugados(int mj);
    void setAsistencias(int a);
    void setTarjetasAmarillas(int ta);
    void setTarjetasRojas(int tr);
    void setFaltas(int f);

    void actualizar(int goles,int amarillas,int rojas,int faltas,int minutos);

    void mostrar();

    EstadisticaJugador& operator=(const EstadisticaJugador& otro);
};

#endif
