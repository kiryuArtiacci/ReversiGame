#include "BusinessLayer.h" //Capa de Negocio, aqui incluye el .h 

//Metodos y aplicaciones del programa, en cada capa se utilizo un nombre generico para no volvernos un desastre nosotros programando y confundiendonos con las capas
JuegoReversi::JuegoReversi() : jugadorActual(Color::Negro) {
}

void JuegoReversi::iniciarJuego() {
    tablero = Tablero();
    jugadorActual = Color::Negro;
}

void JuegoReversi::cambiarTurno() {
    jugadorActual = obtenerOtroJugador(jugadorActual);
}

Color JuegoReversi::obtenerOtroJugador(Color jugador) const {
    return (jugador == Color::Negro) ? Color::Blanco : Color::Negro;
}

bool JuegoReversi::hayMovimientoValido(Color jugador) const {
    return tablero.hayMovimientoValido(jugador);
}

bool JuegoReversi::movimientoValido(int fila, int columna) const {
    return tablero.movimientoValido(fila, columna, jugadorActual);
}

void JuegoReversi::hacerMovimiento(int fila, int columna) {
    tablero.hacerMovimiento(fila, columna, jugadorActual);
}

bool JuegoReversi::juegoTerminado() const {
    return tablero.juegoTerminado();
}

Color JuegoReversi::determinarGanador() const {
    return tablero.determinarGanador();
}

Color JuegoReversi::getJugadorActual() const {
    return jugadorActual;
}

const Tablero& JuegoReversi::getTablero() const {
    return tablero;
}
