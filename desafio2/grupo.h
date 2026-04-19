#ifndef GRUPO_H
#define GRUPO_H
class Equipo;
class Partido;

class Grupo{
private:
    char letra;

    Equipo** equipos;
    int cantidadEquipos;

    Partido* partidos;
    int cantidadPartidos;
public:
    //constructor
    Grupo();
    Grupo(const Grupo& copia);

    //destructor
    ~Grupo();

    //getters
    char getLetra();
    int getCantidadEquipos();

    //setter
    void setletra(char letra);

    //metodos principales
    void agregarEquipo(Equipo* equipo);
    void generarPartidos();
    void construirTabla();
    void clasificados();
    //despliegue
    void mostrarGrupo();
    //sobrecarga
    Grupo& operator=(const Grupo& otro);

};

#endif // GRUPO_H
