#ifndef DATALAYER_H
#define DATALAYER_H
//Archivo cabecera de la capa de datos
#include <vector>
using namespace std;
// La clase para los colores de las fichas y el vacio para las casillas sin ficha (se pone el vacio para que sepa cuando hay o no hay una ficha)
enum class Color { Vacio, Negro, Blanco };

//Evidentemente, declaracion de las clases Ficha 
class Ficha {
private:
    Color color;

public:
    Ficha();
    void setColor(Color c);
    Color getColor() const;
    char getChar() const;
};

// Y la clase del tablero
class Tablero {
private:
    vector<vector<Ficha>> tablero; //se usa en encapsulamiento Private, ya que solo necesitamos usar la libreria de vectores para el tablero
	
	 
//Resto de la logica en publc, porque lo demas si se utilizara en public para la interaccion de los demas metodos del tablero con la clase de ficha
public:
    Tablero();
    void imprimir() const;
    bool movimientoValido(int fila, int columna, Color jugador) const;
    void hacerMovimiento(int fila, int columna, Color jugador);
    bool hayMovimientoValido(Color jugador) const;
    int contarFichas(Color jugador) const;
    bool juegoTerminado() const;
    Color determinarGanador() const;
    Color obtenerOtroJugador(Color jugador) const;
};

#endif // DATALAYER_H
