#include <iostream>
#include <cctype>
#include <limits> 
#include "BusinessLayer.h"

using namespace std;
//Logica para ir imprimiendo tablero y la ficha
void imprimirTablero(const Tablero& tablero) {
    tablero.imprimir();
}

Color obtenerOtroJugador(Color jugador) {
    return (jugador == Color::Negro) ? Color::Blanco : Color::Negro;
}

//Logica para la opcion de Jugar contra otro humano
void jugarContraHumano(JuegoReversi& juego) {
    while (!juego.juegoTerminado()) { //Ciclo while para que el juego se mantenga hasta que las reglas de reversi digan que termines (o hasta que cierres la ventana)
        imprimirTablero(juego.getTablero());

        if (!juego.hayMovimientoValido(juego.getJugadorActual())) {
            cout << "No hay movimientos validos para ";
            if (juego.getJugadorActual() == Color::Negro)
                cout << "Negro";
            else
                cout << "Blanco";
            cout << ". Pasa el turno." << endl;
            juego.cambiarTurno();

            if (!juego.hayMovimientoValido(juego.getJugadorActual())) {
                cout << "No hay más movimientos validos. ¡Juego terminado!" << endl;
                break;
            }
        }
		//variables para indicar la columa y la fila
        char columna;
        int fila;
        cout << "Turno del Jugador ";
        if (juego.getJugadorActual() == Color::Negro) //condicionales para saber de quien sera el turno
            cout << "Negro";
        else
            cout << "Blanco";
        cout << ". Ingresa tu movimiento (fila columna): ";

        if (!(cin >> fila >> columna)) {
            cout << "Entrada invalida. Intenta nuevamente." << endl;
            cin.clear(); // Limpiar los indicadores de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada incorrecta
            continue;
        }

        columna = tolower(columna);

        if (fila < 1 || fila > 8 || columna < 'a' || columna > 'h') {
            cout << "Movimiento invalido. Ingresa una fila (1-8) y una columna (a-h) validas." << endl;
            continue;
        }

        int columnaNum = columna - 'a';
        if (juego.movimientoValido(fila - 1, columnaNum)) {
            juego.hacerMovimiento(fila - 1, columnaNum);
            juego.cambiarTurno();
        } else {
            cout << "Movimiento invalido. Intenta nuevamente." << endl;
        }
    }

    // Juego terminado, determinar el ganador
    Color ganador = juego.determinarGanador();
    if (ganador == Color::Vacio) {
        cout << "¡Empate!" << endl;
    } else {
        cout << "¡El ganador es ";
        if (ganador == Color::Negro)
            cout << "Negro";
        else
            cout << "Blanco";
        cout << "!" << endl;
    }
}

//Funcion para el bot, no tiene una IA muy avanzada, solo usara el primer movimiento valido que encuentre
void jugarContraComputadora(JuegoReversi& juego) {
    while (!juego.juegoTerminado()) { //ciclo while que se usa para que el bot siga jugando, mientras el juego no termine
        imprimirTablero(juego.getTablero());

        if (!juego.hayMovimientoValido(juego.getJugadorActual())) { //condicional para que detecte la existencia de movimientos validos
            cout << "No hay movimientos validos para ";
            if (juego.getJugadorActual() == Color::Negro)
                cout << "Negro";
            else
                cout << "Blanco";
            cout << ". Pasa el turno." << endl;
            juego.cambiarTurno();

            if (!juego.hayMovimientoValido(juego.getJugadorActual())) {
                cout << "No hay más movimientos validos. ¡Juego terminado!" << endl;
                break;
            }
        }

        if (juego.getJugadorActual() == Color::Negro) {
            // Turno del humano
            char columna;
            int fila;
            cout << "Turno del Jugador Negro. Ingresa tu movimiento (fila columna): ";

            if (!(cin >> fila >> columna)) {
                cout << "Entrada invalida. Intenta nuevamente." << endl;
                cin.clear(); // Limpiar los indicadores de error
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); /* Descarta la entrada incorrecta, sin las lineas de codigo de esta condicional y este ignore */
                continue;											/* sucedera un bug donde se imprimira infinitamente todo lo que hay en la consola y no permitira seguir jugando*/
            }

            columna = tolower(columna);

            if (fila < 1 || fila > 8 || columna < 'a' || columna > 'h') {
                cout << "Movimiento invalido. Ingresa una fila (1-8) y una columna (a-h) validas." << endl;		//Por si un jugador pone filas o clumnas invalidas
                continue;
            }

            int columnaNum = columna - 'a';
            if (juego.movimientoValido(fila - 1, columnaNum)) {
                juego.hacerMovimiento(fila - 1, columnaNum);
                juego.cambiarTurno();
            } else {
                cout << "Movimiento invalido. Intenta nuevamente." << endl;
            }
        } else {
            // Turno de la computadora (jugador Blanco)
            cout << "Turno de la computadora (Blanco)." << endl;
            bool movimientoRealizado = false;
            for (int i = 0; i < 8 && !movimientoRealizado; ++i) {
                for (int j = 0; j < 8 && !movimientoRealizado; ++j) {
                    if (juego.movimientoValido(i, j)) {
                        juego.hacerMovimiento(i, j);
                        juego.cambiarTurno();
                        movimientoRealizado = true;
                    }
                }
            }
        }
    }

    // Juego terminado, determinar el ganador
    Color ganador = juego.determinarGanador();
    if (ganador == Color::Vacio) {
        cout << "¡Empate!" << endl;
    } else {
        cout << "¡El ganador es ";
        if (ganador == Color::Negro)
            cout << "Negro";
        else
            cout << "Blanco";
        cout << "!" << endl;
    }
}
// Función principal
int main() {
    JuegoReversi juego;
    juego.iniciarJuego();  // Inicia el juego

    int opcion;
    do {	
        // Menú principal
        cout << "Bienvenido a Reversi" << endl;
        cout << "Selecciona una opcion:" << endl;
        cout << "1. Jugar contra otro humano" << endl;
        cout << "2. Jugar contra la computadora" << endl;
        cout << "3. Integrantes del equipo" << endl;
        cout << "4. Reglas" << endl;
        cout << "5. Salir" << endl;  // Opción para salir del menú
        cin >> opcion;

        // Maneja la opción seleccionada
        if (opcion == 1) {
            jugarContraHumano(juego);
        } else if (opcion == 2) {
            jugarContraComputadora(juego);    
        } else if (opcion == 3) {
            cout << "Ernesto Balbás V. 30.932.082" << endl;
            cout << "Aaron Malpica" << endl;
            cout << "Aurismar Marquez" << endl;
        } else if (opcion == 4) {
            cout << "Reglas de Reversi: " << endl;
            cout << "El juego se juega en un tablero de 8x8. " << endl;
            cout << "Hay dos jugadores, uno con fichas negras y otro con fichas blancas. \n" 
					"El objetivo es tener mas fichas de tu color que el oponente al final del juego. \n"
					"Un movimiento es valido si al colocar una ficha se flanquea una o mas fichas del oponente en linea recta. \n"
					"Las fichas flanqueadas se convierten al color del jugador que hizo el movimiento. \n"  << endl;
        } else if (opcion != 5) {
            cout << "Opción inválida. Intenta nuevamente." << endl;
        }
    } while (opcion != 5);  // El menú se repite hasta que se seleccione la opción de salir

    cout << "Saliendo del juego. ¡Gracias por jugar!" << endl;
    return 0;
}
