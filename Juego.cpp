#include "../include/Juego.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <cctype>
using namespace std;

Juego::Juego() : turno(Color::BLANCO) {}

bool Juego::parseCoord(const string& s, Pos& out) const {
    string t;
    for (char ch : s)
        if (!isspace((unsigned char)ch))
            t.push_back(ch);
    if (t.size() < 2 || t.size() > 3) return false;
    char col = toupper(t[0]);
    if (col < 'A' || col > 'J') return false;
    int c = col - 'A';
    string num = t.substr(1);
    for (char ch : num)
        if (!isdigit((unsigned char)ch)) return false;
    int fila = stoi(num);
    if (fila < 1 || fila > 10) return false;

    // Conversión consistente: input fila 1 -> índice 9, fila 10 -> índice 0
    out = Pos(10 - fila, c);
    return true;
}

string Juego::posToStr(const Pos& p) const {
    char col = 'A' + p.col;
    int fila = 10 - p.fila;
    ostringstream os;
    os << col << fila;
    return os.str();
}

void Juego::iniciar() { this->menu(); }

void Juego::menu() {
    while (true) {
        cout << "\n=== DAMAS INTERNACIONALES ===\n";
        cout << "1) Iniciar partida\n2) Reglas\n3) Salir\nElija: ";
        int op;
        if (!(cin >> op)) {
            cin.clear();
            string dum; getline(cin, dum);
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (op == 1) { jugar(); break; }
        else if (op == 2) {
            cout << "\nReglas (resumen):\n";
            cout << "- Tablero 10x10. Piezas en casillas oscuras.\n";
            cout << "- Blancas: 'b' (B dama). Negras: 'n' (N dama).\n";
            cout << "- Blancas comienzan.\n";
            cout << "- Captura obligatoria si existe.\n\n";
            system("pause");
        } else if (op == 3) break;
    }
}

void Juego::jugar() {
    tablero.inicializar();
    turno = Color::BLANCO;

    while (true) {
        tablero.mostrar();
        cout << "Turno de: " << (turno == Color::BLANCO ? "BLANCO (b)" : "NEGRO (n)") << "\n";

        if (!tieneMovimientos(turno)) {
            cout << (turno == Color::BLANCO ? "Blanco" : "Negro") << " no tiene movimientos. ";
            cout << (turno == Color::BLANCO ? "Negro" : "Blanco") << " gana.\n";
            break;
        }

        bool ok = turnoJugador();
        if (!ok) { cout << "Partida interrumpida.\n"; break; }

        Color opponent = (turno == Color::BLANCO ? Color::NEGRO : Color::BLANCO);
        if (tablero.contar(opponent) == 0) {
            tablero.mostrar();
            cout << (turno == Color::BLANCO ? "Blanco" : "Negro") << " ha ganado.\n";
            break;
        }
        turno = opponent;
    }
}

bool Juego::tieneMovimientos(Color c) const {
    auto fichas = tablero.fichasDe(c);
    for (auto &p : fichas)
        if (!tablero.movimientosSimples(p).empty() || !tablero.capturasDesde(p).empty())
            return true;
    return false;
}

bool Juego::turnoJugador() {
    bool capturaOblig = tablero.hayCaptura(turno);
    if (capturaOblig) cout << "ATENCIÓN: existen capturas obligatorias.\n";

    while (true) {
        cout << "Ingrese movimiento (ej: C3 D4) o 'salir': ";
        string line;
        getline(cin, line);
        if (line == "salir" || line == "SALIR") return false;

        istringstream iss(line);
        string s1, s2;
        if (!(iss >> s1 >> s2)) { cout << "Formato inválido. Use: C3 D4\n"; continue; }

        Pos desde, hasta;
        if (!parseCoord(s1, desde) || !parseCoord(s2, hasta)) { cout << "Coordenadas inválidas.\n"; continue; }
        if (!tablero.dentro(desde) || !tablero.dentro(hasta)) { cout << "Fuera del tablero.\n"; continue; }

        const Ficha& f = tablero.ver(desde.fila, desde.col);
        if (f.esVacia()) { cout << "No hay ficha en " << s1 << ".\n"; continue; }
        if ((turno == Color::BLANCO && !f.esBlanca()) || (turno == Color::NEGRO && !f.esNegra())) {
            cout << "La ficha seleccionada no es tuya.\n"; continue;
        }
        if (!tablero.ver(hasta.fila, hasta.col).esVacia()) { cout << "La casilla destino no está vacía.\n"; continue; }

        if (ejecutarMovimiento(desde, hasta, capturaOblig)) return true;
        else cout << "Movimiento inválido.\n";
    }
}

bool Juego::ejecutarMovimiento(const Pos& desde, const Pos& hasta, bool capturaOblig) {
    const Ficha f = tablero.ver(desde.fila, desde.col);
    auto simples = tablero.movimientosSimples(desde);
    auto caps = tablero.capturasDesde(desde);

    bool esSimple = false;
    for (auto& m : simples) if (m == hasta) esSimple = true;

    bool esCaptura = false;
    Pos saltada;
    for (auto& p : caps) if (p.first == hasta) { esCaptura = true; saltada = p.second; }

    if (capturaOblig && !esCaptura) {
        cout << "Debe ejecutar una captura cuando exista.\n";
        return false;
    }

    if (esSimple) {
        tablero.get(hasta.fila, hasta.col) = tablero.get(desde.fila, desde.col);
        tablero.get(desde.fila, desde.col) = Ficha();
        coronar(hasta);
        return true;
    } else if (esCaptura) {
        tablero.get(hasta.fila, hasta.col) = tablero.get(desde.fila, desde.col);
        tablero.get(desde.fila, desde.col) = Ficha();
        tablero.get(saltada.fila, saltada.col) = Ficha();
        coronar(hasta);
        return true;
    } else return false;
}

void Juego::coronar(const Pos& p) {
    Ficha& f = tablero.get(p.fila, p.col);
    if (f.tipo == TipoFicha::NORMAL) {
        if (f.esBlanca() && p.fila == 0) f.tipo = TipoFicha::DAMA;
        if (f.esNegra() && p.fila == 9) f.tipo = TipoFicha::DAMA;
    }
}
