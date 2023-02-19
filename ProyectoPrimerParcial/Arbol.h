#pragma once
#include <iostream>
#include "Grafo.h"
#include <vector>

using namespace std;

struct Nodo_informacion
{
    string nombre = "";
    float costo_acumulado = 0;
    int profundidad = 0;
};

struct Nodo_del_arbol
{
    Nodo_informacion contenido;
    int padre = -1;
    vector<int> hijos;
};

class Arbol
{
    public:
        Arbol();
        bool devuelve_informacion_de_un_vertice_grafo_no_dirigido(string, int, Nodo&, Nodo_informacion&) const;
		void agrega_hijo_a_un_nodo(int padre, Nodo_informacion contenido);
		bool esta_un_nodo_en_ancestros(int nodo_origen, string nombre_del_nodo) const;
    private:
        vector<Nodo_del_arbol> arbol_de_busqueda;
};
