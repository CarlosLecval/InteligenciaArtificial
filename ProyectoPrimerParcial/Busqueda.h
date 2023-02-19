#pragma once
#include <iostream>
#include "Grafo.h"
#include "Arbol.h"

using namespace std;

class Busqueda
{
    public:
        Busqueda();
        bool busqueda_a_lo_ancho(string, string, int&);
        bool busqueda_primero_en_profundidad(string, string, int&);
        bool busqueda_primero_en_profundidad_limitada(string nodo_inicio, string nodo_final, int& nodo_encontrado, int profundidad);
        bool busqueda_primero_en_profundidad_iterativa(string nodo_inicio, string nodo_final, int& nodo_encontrado);
        bool busqueda_bidireccional(string nodo_inicio, string nodo_final, int& nodo_encontrado);
        bool busqueda_ascenso_a_la_colina(string nodo_inicio, string nodo_final, int& nodo_encontrado);
        bool busqueda_primero_el_mejor(string nodo_inicio, string nodo_final, int& nodo_encontrado);
        bool beam_search(string nodo_inicio, string nodo_final, int& nodo_encontrado, int k);
        bool branch_and_bound(string nodo_inicio, string nodo_final, int& nodo_encontrado);
        bool busqueda_a_estrella(string nodo_inicio, string nodo_final, int& nodo_encontrado);
        string devuelve_la_ruta_encontrada(int nodo_encontrado) const;
    private:
        Arbol arbol_de_busqueda;
        Grafo grafo;
};
