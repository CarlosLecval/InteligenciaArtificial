#pragma once
#include <iostream>
#include "Arbol.h"
#include <stack>
#include <queue>
#include <deque>
#include <math.h>
#include <algorithm>

using namespace std;


class Busqueda
{
    public:
        Busqueda();
        bool best_first(string, string, int&);
        bool branch_and_bound(string nodo_inicio, string nodo_final, int& nodo_encontrado);
        string devuelve_la_ruta_encontrada(int nodo_encontrado) const;
    private:
        Arbol arbol_de_busqueda;
};
