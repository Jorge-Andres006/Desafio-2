#ifndef TABLAGRUPO_H
#define TABLAGRUPO_H

class Equipo;
class Grupo;

class TablaGrupo {
private:
    Grupo *grupo;
    Equipo **equipos;
    int *puntos;
    int *partidosJugados;
    int *partidosGanados;
    int *partidosEmpatados;
    int *partidosPerdidos;
    int *diferenciaGol;

    int cantidad;

public:
    // Constructores
    TablaGrupo(Grupo &grupo);
    TablaGrupo(const TablaGrupo &copia); // constructor copia

    // Destructor
    ~TablaGrupo();
    // Getters
    int getCantidad()const;
    int getPuntos(int i)const;
    int getDiferenciaGol(int i)const;
    Equipo *getEquipo(int i)const;

    // Operaciones principales
    void calcularPuntos();
    void ordenarTabla();

    // Resultados de clasificacion
    Equipo *getPrimero();
    Equipo *getSegundo();

    // Despliegue
    void mostrarTabla();

    // Sobrecarga de operador
    TablaGrupo &operator=(const TablaGrupo &otro);
};

#endif // TABLAGRUPO_H
