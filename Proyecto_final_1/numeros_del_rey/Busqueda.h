#pragma once
#include <iostream>
#include "Grafo.h"
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
        Busqueda(Grafo);
        bool busqueda_primero_en_profundidad_numeros_del_rey(int, int&);
        string devuelve_la_ruta_encontrada_numeros_del_rey(int nodo_encontrado) const;
    private:
        Arbol arbol;
        Grafo grafo;
};
