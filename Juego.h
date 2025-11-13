#ifndef JUEGO_H
#define JUEGO_H

#include "Tablero.h"
#include <string>
class Juego {
public:
    Juego();

    void iniciar(); 
    void menu();     
    void jugar();    

private:
    Tablero tablero;
    Color turno; 
    
    bool parseCoord(const std::string& s, Pos& out) const;
    std::string posToStr(const Pos& p) const;
    bool tieneMovimientos(Color c) const;
    bool turnoJugador();
    bool ejecutarMovimiento(const Pos& desde, const Pos& hasta, bool capturaOblig);
    void coronar(const Pos& p);
};

#endif // JUEGO_H
