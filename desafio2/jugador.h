#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador{
private:
    char* nombre;
    char* apellido;
    int numero;

    int partidosJugados;
    int goles;
    int minutosJugados;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;
public:
    //constructores
    Jugador();
    Jugador(const Jugador& copia);

    //destructor
    ~Jugador();

    //getters
    char* getNombre();
    char* getApellido();
    int getNumero();
    int getGoles();

    //setters
    void setNombre(const char* nombre);
    void setApellido(const char* apellido);
    void setNumero(int numero);

    //metodos principales
    void actualizarEstadisticas(int goles, int minutos, int amarillas, int rojas, int faltas);

    //despliegue
    void mostrarJugador();

    //sobrecarga
    Jugador& operator=(const Jugador& otro);
};

#endif // JUGADOR_H
