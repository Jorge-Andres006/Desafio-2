#ifndef ESTADISTICAEQUIPO_H
#define ESTADISTICAEQUIPO_H

class EstadisticaEquipo{
private:
    int golesFavor;
    int golesContra;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int minutosJugados;

public:
    EstadisticaEquipo();
    EstadisticaEquipo(const EstadisticaEquipo& copia);
    ~EstadisticaEquipo();

    int getGolesFavor();
    int getGolesContra();
    int getPartidosGanados();
    int getPartidosEmpatados();
    int getPartidosPerdidos();

    void setGolesFavor(int gf);
    void setGolesContra(int gc);
    void setPartidosGanados(int pg);
    void setPartidosEmpatados(int pe);
    void setPartidosPerdidos(int pp);

    void actualizar(int gf,int gc,int resultado);


    void sumarMinutosJugados(int minutos);

    void mostrar();

    EstadisticaEquipo& operator=(const EstadisticaEquipo& otro);
};

#endif
