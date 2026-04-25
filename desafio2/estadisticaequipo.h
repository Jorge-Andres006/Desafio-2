#ifndef ESTADISTICAEQUIPO_H
#define ESTADISTICAEQUIPO_H

class EstadisticaEquipo {
private:
    int golesFavor;
    int golesContra;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int minutosJugados;

public:
    // Constructores
    EstadisticaEquipo();
    EstadisticaEquipo(const EstadisticaEquipo &copia); // constructor copia

    // Destructor
    ~EstadisticaEquipo();

    // Getters
    int getGolesFavor() const;
    int getGolesContra() const;
    int getPartidosGanados() const;
    int getPartidosEmpatados() const;
    int getPartidosPerdidos() const;

    // Setters
    void setGolesFavor(int gf);
    void setGolesContra(int gc);
    void setPartidosGanados(int pg);
    void setPartidosEmpatados(int pe);
    void setPartidosPerdidos(int pp);

    // Operaciones principales
    void actualizar(int gf, int gc, int resultado);
    void sumarMinutosJugados(int minutos);

    // Despliegue
    void mostrar();

    // Sobrecarga de operador
    EstadisticaEquipo &operator=(const EstadisticaEquipo &otro);
};

#endif // ESTADISTICAEQUIPO_H
