#include <iostream>
#include "Grafo.h"
#include "Busqueda.h"
#include <iomanip>

using namespace std;

class Resultados {
    public:
        void printRutas(string nodo_inicio, string nodo_final, Busqueda& b_grafo, bool dirigido, int limite_profunidad, int& costo);
        void printRutasSinProfunidad(string nodo_inicio, string nodo_final, Busqueda& b_grafo, bool dirigido, int& costo);
        void printRutasAberdeen(string nodo_inicio, string nodo_final, Busqueda &b_grafo, bool dirigido, int limite_profunidad, int &costo);
};