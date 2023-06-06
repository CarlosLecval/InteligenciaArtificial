#include "Busqueda.h"

Busqueda::Busqueda(Grafo grafo)
{
    this->grafo = grafo;
}

bool Busqueda::busqueda_primero_en_profundidad_numeros_del_rey(int resultado_a_buscar, int& nodo_encontrado)
{
    stack<int> pila;
    Arbol arbol_de_busqueda;
    Nodo_informacion_numeros_del_rey raiz;
    arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido_numeros_del_rey(1, 1, ' ', raiz);
    arbol_de_busqueda.crea_arbol_numeros_del_rey(raiz);
    pila.push(0);
    while(!pila.empty())
    {
        int nodo_actual = pila.top();
        if(arbol_de_busqueda.devuelve_resultado_de_un_nodo(nodo_actual) == resultado_a_buscar)
        {
            nodo_encontrado = nodo_actual;
            arbol = arbol_de_busqueda;
            cout << devuelve_la_ruta_encontrada_numeros_del_rey(nodo_encontrado) << endl;
        }
        pila.pop();
        unordered_map<char, int> vecinos = grafo.devuelve_vecinos_numeros_del_rey(arbol_de_busqueda.devuelve_numero_de_un_nodo(nodo_actual), arbol_de_busqueda.devuelve_resultado_de_un_nodo(nodo_actual));
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido_numeros_del_rey(i->second, arbol_de_busqueda.devuelve_numero_de_un_nodo(nodo_actual)+1, i->first, raiz);
            arbol_de_busqueda.agrega_hijo_a_un_nodo_numeros_del_rey(nodo_actual, raiz);
            pila.push(arbol_de_busqueda.devuelve_tamano_del_arbol_numeros_del_rey() - 1);
        }
    }
    return false;
}

string Busqueda::devuelve_la_ruta_encontrada_numeros_del_rey(int nodo_encontrado) const
{
    vector<int> temporal;
    string camino = "";
    temporal.clear();
    while (nodo_encontrado != -1)
    {
        temporal.push_back(nodo_encontrado);
        nodo_encontrado = arbol.devuelve_padre_de_un_nodo_numeros_del_rey(nodo_encontrado);
    }
    for (int i =(int)temporal.size() - 1; i >= 0; i--)
        camino = camino + " " + arbol.devuelve_operacion_de_un_nodo(temporal[i]) + " " + to_string(arbol.devuelve_numero_de_un_nodo(temporal[i])); 
    camino += " = " + to_string(arbol.devuelve_resultado_de_un_nodo(temporal[0]));
    return camino;
}