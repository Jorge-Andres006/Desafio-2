#ifndef TABLAGRUPO_H
#define TABLAGRUPO_H

class Equipo;
class Grupo;

class TablaGrupo{
private:
    Grupo* grupo;
    Equipo** equipos;
    int* puntos;
    int* partidosJugados;
    int* partidosGanados;
    int* partidosEmpatados;
    int* partidosPerdidos;
    int* diferenciaGol;
    int cantidad;

public:
    // constructores
    TablaGrupo(Grupo& grupo);
    TablaGrupo(const TablaGrupo& copia);

    // destructor
    ~TablaGrupo();

    // getters
    int getCantidad();
    int getPuntos(int i);
    Equipo* getEquipo(int i);
    int getDiferenciaGol(int i);

    // métodos principales
    void calcularPuntos();
    void ordenarTabla();

    // despliegue
    void mostrarTabla();

    // resultados
    Equipo* getPrimero();
    Equipo* getSegundo();

    // sobrecarga
    TablaGrupo& operator=(const TablaGrupo& otro);
};

#endif
