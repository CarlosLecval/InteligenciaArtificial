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
    Nodo_informacion raiz;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz);
    arbol_de_busqueda.crea_arbol(raiz);
    cola.push(0);
    while(!cola.empty())
    {
        int nodo_actual = cola.front();
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            arbol = arbol_de_busqueda;
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

bool Busqueda::intersectan(deque<int>& camino_inicio, deque<int>& camino_final, int& nodo_encontrado_inicio, int& nodo_encontrado_final)
{
    for(auto i = camino_inicio.begin(); i != camino_inicio.end(); i++)
    {
        for(auto j = camino_final.begin(); j != camino_final.end(); j++)
        {
            if(*i == *j)
            {
                nodo_encontrado_inicio = *i;
                nodo_encontrado_final = *j;
                return true;
            }
        }
    }
    return false;
}

bool Busqueda::busqueda_bidireccional(string nodo_inicio, string nodo_final, int& nodo_encontrado_inicio, int& nodo_encontrado_final)
{
    deque<int> camino_inicio;
    deque<int> camino_final;
    Arbol arbol_de_busqueda_inicio;
    Arbol arbol_de_busqueda_final;
    Nodo raiz_nodo;
    Nodo_informacion raiz;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    arbol_de_busqueda_inicio.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz);
    arbol_de_busqueda_inicio.crea_arbol(raiz);
    camino_inicio.push_back(0);
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_final, raiz_nodo)) return false;
    if(!arbol_de_busqueda_final.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_final, -1, raiz_nodo, raiz)) return false;
    arbol_de_busqueda_final.crea_arbol(raiz);
    camino_final.push_front(0);
    while(!camino_inicio.empty() && !camino_final.empty())
    {
        int nodo_actual = camino_inicio.front();
        if(arbol_de_busqueda_inicio.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado_inicio = nodo_actual;
            arbol = arbol_de_busqueda_inicio;
            return true;
        }
        camino_inicio.pop_front();
        vector<Enlace> vecinos = grafo.devuelve_vecinos_de_un_nodo(arbol_de_busqueda_inicio.devuelve_nombre_de_un_nodo(nodo_actual));
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            if(!arbol_de_busqueda_inicio.esta_un_nodo_en_ancestros(nodo_actual, i->nombre)) continue;
            vecinos.erase(i);
            i--;
        }
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            grafo.devuelve_informacion_de_un_nodo(i->nombre, raiz_nodo);
            arbol_de_busqueda_inicio.devuelve_informacion_de_un_vertice_grafo_no_dirigido(i->nombre, nodo_actual, raiz_nodo, raiz);
            arbol_de_busqueda_inicio.agrega_hijo_a_un_nodo(nodo_actual, raiz);
            camino_inicio.push_back(arbol_de_busqueda_inicio.devuelve_tamano_del_arbol() - 1);
        }
        nodo_actual = camino_final.front();
        if(arbol_de_busqueda_final.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_inicio)
        {
            nodo_encontrado_final = nodo_actual;
            arbol = arbol_de_busqueda_final;
            return true;
        }
        camino_final.pop_front();
        vecinos = grafo.devuelve_vecinos_de_un_nodo(arbol_de_busqueda_final.devuelve_nombre_de_un_nodo(nodo_actual));
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            if(!arbol_de_busqueda_final.esta_un_nodo_en_ancestros(nodo_actual, i->nombre)) continue;
            vecinos.erase(i);
            i--;
        }
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            grafo.devuelve_informacion_de_un_nodo(i->nombre, raiz_nodo);
            arbol_de_busqueda_final.devuelve_informacion_de_un_vertice_grafo_no_dirigido(i->nombre, nodo_actual, raiz_nodo, raiz);
            arbol_de_busqueda_final.agrega_hijo_a_un_nodo(nodo_actual, raiz);
            camino_final.push_front(arbol_de_busqueda_final.devuelve_tamano_del_arbol() - 1);
        }
        if(intersectan(camino_inicio, camino_final, nodo_encontrado_inicio, nodo_encontrado_final))
        {
            arbol = arbol_de_busqueda_inicio;
            arbol_final = arbol_de_busqueda_final;
            return true;
        }
    }
    return false;
}

bool Busqueda::busqueda_ascenso_a_la_colina(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    Nodo raiz_nodo;
    Nodo_informacion raiz;
    Arbol arbol_de_busqueda;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz);
    arbol_de_busqueda.crea_arbol(raiz);
    int* max_num = new int(0);
    while(max_num != NULL)
    {
        int nodo_actual = *max_num;
        max_num = NULL;
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            arbol = arbol_de_busqueda;
            return true;
        }
        vector<Enlace> vecinos = grafo.devuelve_vecinos_de_un_nodo(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual));
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            if(!arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, i->nombre)) continue;
            vecinos.erase(i);
            i--;
        }
        Nodo_informacion temp_max;
        for(auto i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_nodo(vecinos[i].nombre, raiz_nodo);
            arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nombre, nodo_actual, raiz_nodo, raiz);
            if(max_num == NULL || raiz.costo_acumulado > temp_max.costo_acumulado)
            {
                max_num = new int(i);
                temp_max = raiz;
            }
        }
        if(max_num != NULL)
        {
            arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual, temp_max);
        }
        else break;
    }
    arbol = arbol_de_busqueda;
    return false;
}
