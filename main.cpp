#include <iostream>
using namespace std;

const int SIZE = 10;

// Función para mostrar el tablero
void mostrarTablero(char tablero[SIZE][SIZE]) {
    cout << "   ";
    for (int c = 0; c < SIZE; c++)
        cout << c << " ";
    cout << endl;

    for (int f = 0; f < SIZE; f++) {
        cout << f << "  ";
        for (int c = 0; c < SIZE; c++) {
            cout << tablero[f][c] << " ";
        }
        cout << endl;
    }
}

int main() {
    char tablero[SIZE][SIZE];

    for (int f = 0; f < SIZE; f++) {
        for (int c = 0; c < SIZE; c++) {
            tablero[f][c] = '-';
        }
    }

    cout << "=== JUEGO DE DAMAS INTERNACIONALES ===" << endl;
    mostrarTablero(tablero);
    return 0;
}
