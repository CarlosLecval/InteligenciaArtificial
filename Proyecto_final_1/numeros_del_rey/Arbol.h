#pragma once
#include <iostream>
#include "Grafo.h"
#include <vector>

using namespace std;

struct Nodo_informacion_numeros_del_rey
{
    int resultado = 0;
    int numero = 0;
    char operacion = ' ';
};

struct Nodo_del_arbol_numeros_del_rey
{
    Nodo_informacion_numeros_del_rey contenido;
    int padre = -1;
    vector<int> hijos;
};

class Arbol
{
    public:
        Arbol();
        void crea_arbol_numeros_del_rey(Nodo_informacion_numeros_del_rey);
        void devuelve_informacion_de_un_vertice_grafo_no_dirigido_numeros_del_rey(int resultado, int numero, char operacion, Nodo_informacion_numeros_del_rey& informacion_nodo);
        void agrega_hijo_a_un_nodo_numeros_del_rey(int padre, Nodo_informacion_numeros_del_rey contenido);
        int devuelve_tamano_del_arbol_numeros_del_rey() const;
        int devuelve_padre_de_un_nodo_numeros_del_rey(int posicion) const;
        int devuelve_resultado_de_un_nodo(int) const;
        int devuelve_numero_de_un_nodo(int) const;
        char devuelve_operacion_de_un_nodo(int) const;
    private:
        vector<Nodo_del_arbol_numeros_del_rey> arbol_de_busqueda_numeros_del_rey;
};
