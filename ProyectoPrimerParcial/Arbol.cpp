#include "Arbol.h"

Arbol::Arbol()
{
}

void Arbol::crea_arbol(Nodo_informacion contenido)
{
    Nodo_del_arbol temporal;
    temporal.contenido = contenido;
    temporal.hijos.clear();
    arbol_de_busqueda.push_back(temporal);
}

bool Arbol::devuelve_informacion_de_un_vertice_grafo_no_dirigido(int padre_nodo, Nodo& nodo, Nodo_informacion& informacion_nodo)
{
    informacion_nodo.nombre = nodo.nombre;
    informacion_nodo.costo_acumulado = arbol_de_busqueda[padre_nodo].contenido.costo_acumulado + nodo.costo_ciudad;
    informacion_nodo.profundidad = arbol_de_busqueda[padre_nodo].contenido.profundidad + 1;
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