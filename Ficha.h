#ifndef FICHA_H
#define FICHA_H

// Enumeración para identificar el color de cada ficha
enum class Color { VACIO, BLANCO, NEGRO };

enum class TipoFicha { NORMAL, DAMA };

// Estructura base que representa una ficha en el tablero
struct Ficha {
    Color color;
    TipoFicha tipo;
    // Constructor 
    Ficha(Color c = Color::VACIO, TipoFicha t = TipoFicha::NORMAL);
    bool esVacia() const;
    bool esBlanca() const;
    bool esNegra() const;
};

#endif // FICHA_H

