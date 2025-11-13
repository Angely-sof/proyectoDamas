#include "../include/Tablero.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

void Tablero::inicializar() {
    for (int f = 0; f < 10; ++f)
        for (int c = 0; c < 10; ++c)
            celdas[f][c] = Ficha();
   // Fichas negras
    for (int f = 0; f < 4; ++f)
        for (int c = 0; c < 10; ++c)
            if ((f + c) % 2 == 1)
                celdas[f][c] = Ficha(Color::NEGRO);
 // Fichas blancas
    for (int f = 6; f < 10; ++f)
        for (int c = 0; c < 10; ++c)
            if ((f + c) % 2 == 1)
                celdas[f][c] = Ficha(Color::BLANCO);
}

static void print_sep() {
    cout << "    +";
    for (int i = 0; i < 10; ++i) cout << "---+";
    cout << "\n";
}

void Tablero::mostrar() const {
    system("cls"); // Limpia la consola antes de mostrar
    cout << "\n      ";
    for (char c = 'A'; c <= 'J'; ++c) cout << " " << c << "  ";
    cout << "\n";

    print_sep();

    for (int f = 0; f < 10; ++f) {
        int displayRow = 10 - f; 
        cout << setw(3) << displayRow << " |";
        for (int c = 0; c < 10; ++c) {
            const Ficha &F = celdas[f][c];
            char ch = ' ';
            if (F.esBlanca()) ch = (F.tipo == TipoFicha::DAMA ? 'B' : 'b');
            else if (F.esNegra()) ch = (F.tipo == TipoFicha::DAMA ? 'N' : 'n');
            cout << " " << ch << " |";
        }
        cout << " " << setw(2) << displayRow << "\n";
        print_sep();
    }

    cout << "      ";
    for (char c = 'A'; c <= 'J'; ++c) cout << " " << c << "  ";
    cout << "\n\n";
}

bool Tablero::dentro(const Pos& p) const {
    return p.fila >= 0 && p.fila < 10 && p.col >= 0 && p.col < 10;
}

Ficha& Tablero::get(int f, int c) { return celdas[f][c]; }
const Ficha& Tablero::ver(int f, int c) const { return celdas[f][c]; }

vector<Pos> Tablero::fichasDe(Color c) const {
    vector<Pos> v;
    for (int f = 0; f < 10; ++f)
        for (int cc = 0; cc < 10; ++cc)
            if (celdas[f][cc].color == c)
                v.push_back(Pos(f, cc));
    return v;
}
//sin captura
vector<Pos> Tablero::movimientosSimples(const Pos& p) const {
    vector<Pos> moves;
    const Ficha& F = ver(p.fila, p.col);
    if (F.esVacia()) return moves;

    int dir = (F.esBlanca() ? -1 : 1); // Blancas suben, negras bajan
    int dr[2] = { dir, dir };
    int dc[2] = { -1, 1 };

    for (int i = 0; i < 2; ++i) {
        Pos np(p.fila + dr[i], p.col + dc[i]);
        if (dentro(np) && ver(np.fila, np.col).esVacia())
            moves.push_back(np);
    }
    return moves;
}

//posibles capturas
vector<pair<Pos, Pos>> Tablero::capturasDesde(const Pos& p) const {
    vector<pair<Pos, Pos>> caps;
    const Ficha& F = ver(p.fila, p.col);
    if (F.esVacia()) return caps;

    // Movimientos diagonales posibles
    int dirs[4][2] = { {-1,-1}, {-1,1}, {1,-1}, {1,1} };

    for (auto& d : dirs) {
        Pos mid(p.fila + d[0], p.col + d[1]);
        Pos dest(p.fila + 2*d[0], p.col + 2*d[1]);

        if (!dentro(mid) || !dentro(dest)) continue;

        const Ficha& fm = ver(mid.fila, mid.col);
        const Ficha& fd = ver(dest.fila, dest.col);

        if (!fm.esVacia() && fm.color != F.color && fd.esVacia())
            caps.push_back({dest, mid});
    }
    return caps;
}

bool Tablero::hayCaptura(Color c) const {
    for (int f = 0; f < 10; ++f)
        for (int cc = 0; cc < 10; ++cc)
            if (celdas[f][cc].color == c && !capturasDesde(Pos(f,cc)).empty())
                return true;
    return false;
}

int Tablero::contar(Color c) const {
    int cnt = 0;
    for (int f = 0; f < 10; ++f)
        for (int cc = 0; cc < 10; ++cc)
            if (celdas[f][cc].color == c)
                cnt++;
    return cnt;
}

