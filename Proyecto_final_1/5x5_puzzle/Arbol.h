#pragma once
#include <iostream>
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
        Arbol(string nodo_final);
        void crea_arbol(Nodo_informacion);
        void devuelve_informacion_de_un_vertice_grafo_no_dirigido(string nombre_nodo, int padre, Nodo_informacion& informacion_nodo);
        vector<string> devuelve_vecinos_de_un_nodo (string nombre_nodo);
        int devuelve_profundidad_del_nodo(int posicion);
        float devuelve_costo_acumulado_del_nodo(int posicion) const;
		void agrega_hijo_a_un_nodo(int padre, Nodo_informacion contenido);
		bool esta_un_nodo_en_ancestros(int nodo_origen, string nodo_presunto_ancestro) const;
        int devuelve_tamano_del_arbol() const;
        int devuelve_padre_de_un_nodo(int posicion) const;
        int devuelve_heuristica(int posicion);
        bool validar_estado(string nombre_nodo);
        string devuelve_nombre_de_un_nodo(int) const;
    private:
        string nodo_final;
        vector<Nodo_del_arbol> arbol_de_busqueda;
};
