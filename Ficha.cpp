#include "../include/Ficha.h"

// Constructor
Ficha::Ficha(Color c, TipoFicha t) : color(c), tipo(t) {}
bool Ficha::esVacia() const { return color == Color::VACIO; }
bool Ficha::esBlanca() const { return color == Color::BLANCO; }
bool Ficha::esNegra() const { return color == Color::NEGRO; }
