#ifndef BUSINESSLAYER_H
#define BUSINESSLAYER_H

#include "DataLayer.h" //este es el archivo cabecera de la capa de Negocio

class JuegoReversi {
private:		//Encapsulamiento privado, ya que solo se trabajaran en metodos y funciones que el usuario no debera manipular
    Tablero tablero;
    Color jugadorActual;

    Color obtenerOtroJugador(Color jugador) const; 

public:		//Encapsulamiento publico, todo esto es lo que si tratara con el usuario, ya que son los metodos de la secuencia del juego reversi
    JuegoReversi();
    void iniciarJuego();
    void cambiarTurno();
    bool hayMovimientoValido(Color jugador) const;
    bool movimientoValido(int fila, int columna) const;
    void hacerMovimiento(int fila, int columna);
    bool juegoTerminado() const;
    Color determinarGanador() const;
    Color getJugadorActual() const;
    const Tablero& getTablero() const;
};

#endif // BUSINESSLAYER_H
