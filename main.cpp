#include <windows.h>
#include <iostream>
#include "include/Juego.h"

int main() {
    // Configura la consola de Windows para mostrar caracteres UTF-8 correctamente
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Juego juego;
    juego.menu();
    std::cout << "\nGracias por jugar.\n";
    system("pause");
    return 0;
}

