#include "Arbol.h"

Arbol::Arbol()
{
}

void Arbol::crea_arbol_numeros_del_rey(Nodo_informacion_numeros_del_rey contenido)
{
    arbol_de_busqueda_numeros_del_rey.clear();
    Nodo_del_arbol_numeros_del_rey temporal;
    temporal.contenido = contenido;
    temporal.hijos.clear();
    arbol_de_busqueda_numeros_del_rey.push_back(temporal);
}

void Arbol::devuelve_informacion_de_un_vertice_grafo_no_dirigido_numeros_del_rey(int resultado, int numero, char operacion, Nodo_informacion_numeros_del_rey& informacion_nodo)
{
    informacion_nodo.resultado = resultado;
    informacion_nodo.numero = numero;
    informacion_nodo.operacion = operacion;
}

void Arbol::agrega_hijo_a_un_nodo_numeros_del_rey(int padre, Nodo_informacion_numeros_del_rey contenido)
{
    Nodo_del_arbol_numeros_del_rey temporal;
    temporal.contenido = contenido;
    temporal.padre = padre;
    temporal.hijos.clear();
    arbol_de_busqueda_numeros_del_rey.push_back(temporal);
    arbol_de_busqueda_numeros_del_rey[padre].hijos.push_back((unsigned int)arbol_de_busqueda_numeros_del_rey.size() - 1);
}

int Arbol::devuelve_padre_de_un_nodo_numeros_del_rey(int nodo) const
{
    return arbol_de_busqueda_numeros_del_rey[nodo].padre;
}

int Arbol::devuelve_resultado_de_un_nodo(int nodo) const
{
    return arbol_de_busqueda_numeros_del_rey[nodo].contenido.resultado;
}

int Arbol::devuelve_numero_de_un_nodo(int nodo) const
{
    return arbol_de_busqueda_numeros_del_rey[nodo].contenido.numero;
}

char Arbol::devuelve_operacion_de_un_nodo(int nodo) const
{
    return arbol_de_busqueda_numeros_del_rey[nodo].contenido.operacion;
}

int Arbol::devuelve_tamano_del_arbol_numeros_del_rey() const
{
    return (int)arbol_de_busqueda_numeros_del_rey.size();
}