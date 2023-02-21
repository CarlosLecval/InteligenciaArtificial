#include "Busqueda.h"

Busqueda::Busqueda(Grafo grafo)
{
    this->grafo = grafo;
}

bool Busqueda::busqueda_a_lo_ancho(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    queue<int> cola;
    Arbol arbol_de_busqueda;
    Nodo raiz_nodo;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    Nodo_informacion raiz;
    if(!arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz)) return false;
    arbol_de_busqueda.crea_arbol(raiz);
    cola.push(0);
    while(!cola.empty())
    {
        int nodo_actual = cola.front();
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        cola.pop();
        vector<Enlace> vecinos = grafo.devuelve_vecinos_de_un_nodo(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual));
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            if(!arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, i->nombre)) continue;
            vecinos.erase(i);
            i--;
        }
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            grafo.devuelve_informacion_de_un_nodo(i->nombre, raiz_nodo);
            arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(i->nombre, nodo_actual, raiz_nodo, raiz);
            arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual, raiz);
            cola.push(arbol_de_busqueda.devuelve_tamano_del_arbol() - 1);
        }
    }
    return false;
}
