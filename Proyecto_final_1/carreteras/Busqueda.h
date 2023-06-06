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
        bool busqueda_a_lo_ancho(string, string, int&);
        bool busqueda_primero_en_profundidad(string, string, int&);
        bool busqueda_primero_en_profundidad_limitada(string nodo_inicio, string nodo_final, int& nodo_encontrado, int profundidad);
        bool busqueda_primero_en_profundidad_iterativa(string nodo_inicio, string nodo_final, int& nodo_encontrado,int primera_profundidad,int incremento_profundidad);
        bool busqueda_bidireccional(string nodo_inicio, string nodo_final, int& nodo_encontrado_inicio, int& nodo_encontrado_final);
        bool busqueda_ascenso_a_la_colina(string nodo_inicio, string nodo_final, int& nodo_encontrado);
        bool busqueda_primero_el_mejor(string nodo_inicio, string nodo_final, int& nodo_encontrado);
        bool beam_search(string nodo_inicio, string nodo_final, int& nodo_encontrado, int k);
        bool branch_and_bound(string nodo_inicio, string nodo_final, int& nodo_encontrado);
        bool busqueda_a_estrella(string nodo_inicio, string nodo_final, int& nodo_encontrado);
        string devuelve_la_ruta_encontrada(int nodo_encontrado,int& costo) const;
        string devuelve_la_ruta_bidireccional(int nodo_encontrado_inicio, int nodo_encontrado_final) const;
        string devuelve_max_agenda() const;
        string devuelve_max_arbol() const;
        void reset_max();
    private:
        Arbol arbol;
        Arbol arbol_final;
        Grafo grafo;
        int max_agenda = -1;
        int max_arbol = -1;
        bool es_costo_mas_heuristica_menor(vector<int>& agenda, float costo_mas_heuristica, Arbol& arbol) const;
        void ordena_por_costo_acumulado(vector<int>&,Arbol&,int);
        void ordena_por_costo_mas_heuristica(vector<int>&,Arbol&);
        bool intersectan(deque<int>&, deque<int>&, int&, int&, Arbol&, Arbol&);
};
