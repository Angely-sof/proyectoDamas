#ifndef TABLERO_H
#define TABLERO_H

#include "Ficha.h"
#include <vector>
#include <utility>

struct Pos {
    int fila;
    int col;
    Pos(int f = 0, int c = 0) : fila(f), col(c) {}

    // Comparación de posiciones
    bool operator==(const Pos& o) const { return fila == o.fila && col == o.col; }
};

//lógica 
class Tablero {
public:
    Tablero() = default;
    void inicializar();
    void mostrar() const;
    bool dentro(const Pos& p) const;
    Ficha& get(int f, int c);
    const Ficha& ver(int f, int c) const;
 //lógica de movimiento
    std::vector<Pos> fichasDe(Color c) const;
    std::vector<Pos> movimientosSimples(const Pos& p) const;
    std::vector<std::pair<Pos, Pos>> capturasDesde(const Pos& p) const;
    bool hayCaptura(Color c) const;
    int contar(Color c) const;
private:
    Ficha celdas[10][10];
};

#endif


