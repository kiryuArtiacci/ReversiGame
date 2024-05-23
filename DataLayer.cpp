#include "DataLayer.h"
#include <iostream>
#include <vector>
#include <cctype>

//Capa para datos, esto es como una "Base de datos" que funciona para el programa

using namespace std;
//Constructores de las fichas, esto es para asignar sus colores
Ficha::Ficha() : color(Color::Vacio) {}

//Metodos Sets y Gets
void Ficha::setColor(Color c) {
    color = c;
}

Color Ficha::getColor() const {
    return color;
}

char Ficha::getChar() const {
    switch (color) {
        case Color::Negro:
            return 'N';
        case Color::Blanco:
            return 'B';
        default:
            return '.';
    }
}
//Logica y metodos que hacen que el tablero funcione
Tablero::Tablero() {
    tablero.resize(8, vector<Ficha>(8));
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            tablero[i][j].setColor(Color::Vacio);
        }
    }
    tablero[3][3].setColor(Color::Blanco);
    tablero[3][4].setColor(Color::Negro);
    tablero[4][3].setColor(Color::Negro);
    tablero[4][4].setColor(Color::Blanco);
}

void Tablero::imprimir() const {
    cout << "  a b c d e f g h" << endl;
    for (int i = 0; i < 8; ++i) {
        cout << i + 1 << " ";
        for (int j = 0; j < 8; ++j) {
            cout << static_cast<char>(tablero[i][j].getChar()) << " ";
        }
        cout << endl;
    }
}
//Esto detecta si el movimiento es valido o no, siguiendo las reglas del juego reversi 
bool Tablero::movimientoValido(int fila, int columna, Color jugador) const {
    if (fila < 0 || fila >= 8 || columna < 0 || columna >= 8 || tablero[fila][columna].getColor() != Color::Vacio)
        return false;

    for (int df = -1; df <= 1; ++df) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (df == 0 && dc == 0) continue;
            int f = fila + df;
            int c = columna + dc;
            bool oponenteFlanqueado = false;
            while (f >= 0 && f < 8 && c >= 0 && c < 8 && tablero[f][c].getColor() == obtenerOtroJugador(jugador)) {
                f += df;
                c += dc;
                oponenteFlanqueado = tablero[f][c].getColor() == jugador;
            }
            if (oponenteFlanqueado) return true;
        }
    }
    return false;
}
//Esto le permitira al jugador hacer el propio movimiento, a diferencia de la funcion anterior; que esta para revisar si lo que hara el jugador es valido
void Tablero::hacerMovimiento(int fila, int columna, Color jugador) {
    tablero[fila][columna].setColor(jugador);

    for (int df = -1; df <= 1; ++df) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (df == 0 && dc == 0) continue;
            int f = fila + df;
            int c = columna + dc;
            while (f >= 0 && f < 8 && c >= 0 && c < 8 && tablero[f][c].getColor() == obtenerOtroJugador(jugador)) {
                f += df;
                c += dc;
            }
            if (f >= 0 && f < 8 && c >= 0 && c < 8 && tablero[f][c].getColor() == jugador) {
                f = fila + df;
                c = columna + dc;
                while (f >= 0 && f < 8 && c >= 0 && c < 8 && tablero[f][c].getColor() == obtenerOtroJugador(jugador)) {
                    tablero[f][c].setColor(jugador);
                    f += df;
                    c += dc;
                }
            }
        }
    }
}
//Esto para que revise si hay movimiento valido o no, despues se utilizara en otra funcion
bool Tablero::hayMovimientoValido(Color jugador) const {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (movimientoValido(i, j, jugador))
                return true;
        }
    }
    return false;
}
//Esto para contar las fichas, que es el sistema de puntos del Reversi
int Tablero::contarFichas(Color jugador) const {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (tablero[i][j].getColor() == jugador)
                count++;
        }
    }
    return count;
}

//Esto llama o convoca la funcion para revisar los posibles movimientos validos, en caso de que no hayan movimientos validos el juego termina
bool Tablero::juegoTerminado() const {
    return !hayMovimientoValido(Color::Negro) && !hayMovimientoValido(Color::Blanco);
}

//metodo que llama a la funcion de contar fichas, como mencione antes, es el sistema de puntos del juego
Color Tablero::determinarGanador() const {
    int negro = contarFichas(Color::Negro);
    int blanco = contarFichas(Color::Blanco);
    if (negro > blanco)
        return Color::Negro;	//Hara que diga que gano el negro
    else if (negro < blanco)
        return Color::Blanco;	//lo mismo pero para el blanco
    else
        return Color::Vacio; // Empate
}

Color Tablero::obtenerOtroJugador(Color jugador) const {
    return (jugador == Color::Negro) ? Color::Blanco : Color::Negro;
}
