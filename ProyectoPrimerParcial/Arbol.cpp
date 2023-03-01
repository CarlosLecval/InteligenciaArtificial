#include "Arbol.h"

Arbol::Arbol()
{
}

void Arbol::crea_arbol(Nodo_informacion contenido)
{
    arbol_de_busqueda.clear();
    Nodo_del_arbol temporal;
    temporal.contenido = contenido;
    temporal.hijos.clear();
    arbol_de_busqueda.push_back(temporal);
}

void Arbol::devuelve_informacion_de_un_vertice_grafo_no_dirigido(string nombre_nodo, int padre_nodo, Nodo& nodo, Nodo_informacion& informacion_nodo)
{
    informacion_nodo.nombre = nombre_nodo;
    if(padre_nodo != -1){
        informacion_nodo.costo_acumulado = arbol_de_busqueda[padre_nodo].contenido.costo_acumulado + nodo.costo_ciudad + nodo.vecinos[arbol_de_busqueda[padre_nodo].contenido.nombre];
        informacion_nodo.profundidad = arbol_de_busqueda[padre_nodo].contenido.profundidad + 1;
    }
    else {
        informacion_nodo.costo_acumulado = nodo.costo_ciudad;
        informacion_nodo.profundidad = 0;
    }
}

int Arbol::devuelve_profundidad_del_nodo(int posicion_nodo)
{
    return arbol_de_busqueda[posicion_nodo].contenido.profundidad;
}

int Arbol::devuelve_costo_acumulado_del_nodo(int posicion_nodo) const
{
    return arbol_de_busqueda[posicion_nodo].contenido.costo_acumulado;
}

int Arbol::devuelve_costo_mas_heuristica_del_nodo(int posicion_nodo)
{
    return arbol_de_busqueda[posicion_nodo].contenido.costo_mas_heuristica;
}

void Arbol::agrega_hijo_a_un_nodo(int padre, Nodo_informacion contenido)
{
    Nodo_del_arbol temporal;
    temporal.contenido = contenido;
    temporal.padre = padre;
    temporal.hijos.clear();
    arbol_de_busqueda.push_back(temporal);
    arbol_de_busqueda[padre].hijos.push_back(arbol_de_busqueda.size() - 1);
}

bool Arbol::esta_un_nodo_en_ancestros(int nodo_origen, string nodo_presunto_ancestro) const
{
    while(nodo_origen != -1)
    {
        if(arbol_de_busqueda[nodo_origen].contenido.nombre == nodo_presunto_ancestro)
            return true;
        nodo_origen = arbol_de_busqueda[nodo_origen].padre;
    }
    return false;
}

int Arbol::devuelve_tamano_del_arbol() const
{
    return arbol_de_busqueda.size();
}

string Arbol::devuelve_nombre_de_un_nodo(int nodo) const
{
    return arbol_de_busqueda[nodo].contenido.nombre;
}

int Arbol::devuelve_padre_de_un_nodo(int nodo) const
{
    return arbol_de_busqueda[nodo].padre;
}