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
    arbol_de_busqueda_final.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_final, -1, raiz_nodo, raiz);
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


bool Busqueda::busqueda_primero_en_profundidad(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    stack<int> pila;
    Arbol arbol_de_busqueda;
    Nodo raiz_nodo;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    Nodo_informacion raiz;
    arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz);
    arbol_de_busqueda.crea_arbol(raiz);
    pila.push(0);
    while(!pila.empty())
    {
        int nodo_actual = pila.top();
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            arbol = arbol_de_busqueda;
            return true;
        }
        pila.pop();
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
            pila.push(arbol_de_busqueda.devuelve_tamano_del_arbol() - 1);
        }
    }
    return false;
}

bool Busqueda::busqueda_primero_en_profundidad_limitada(string nodo_inicio, string nodo_final, int& nodo_encontrado, int profundidad_limite)
{
    stack<int> pila;
    Arbol arbol_de_busqueda;
    Nodo raiz_nodo;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;

    Nodo_informacion raiz;

    arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz);

    arbol_de_busqueda.crea_arbol(raiz);
    pila.push(0);

    while(!pila.empty())
    {
        int nodo_actual = pila.top();
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            arbol = arbol_de_busqueda;
            return true;
        }
        pila.pop();

        //solo busca vecinos si la profundidad del grafo es menor al limite
        vector<Enlace> vecinos;
        vecinos.clear();
        if(arbol_de_busqueda.devuelve_profundidad_del_nodo(nodo_actual)<=profundidad_limite)
            vecinos = grafo.devuelve_vecinos_de_un_nodo(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual));

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
            pila.push(arbol_de_busqueda.devuelve_tamano_del_arbol() - 1);
        }
    }
    return false;    
}

bool Busqueda::busqueda_primero_en_profundidad_iterativa(string nodo_inicio, string nodo_final, int& nodo_encontrado,int primera_profundidad,int incremento_profundidad)
{
    Nodo raiz_nodo;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    while(!busqueda_primero_en_profundidad_limitada(nodo_inicio,nodo_final,nodo_encontrado,primera_profundidad))
        primera_profundidad += incremento_profundidad;
    return true;
}

void Busqueda::ordena_por_costo_acumulado(vector<int>& agenda,Arbol& arbol_de_busqueda,int k)
{
    for(int i = 0; i < agenda.size(); i++)
    {
        for(int j = i + 1; j < agenda.size(); j++)
        {
            if(arbol_de_busqueda.devuelve_costo_acumulado_del_nodo(agenda[i]) > arbol_de_busqueda.devuelve_costo_acumulado_del_nodo(agenda[j]))
            {
                int aux = agenda[i];
                agenda[i] = agenda[j];
                agenda[j] = aux;
            }
        }
    }
    
    agenda.erase(agenda.begin() + k, agenda.end());
}

bool Busqueda::busqueda_primero_el_mejor(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    vector<int> agenda;
    Arbol arbol_de_busqueda;
    Nodo raiz_nodo;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    Nodo_informacion raiz;
    arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz);
    arbol_de_busqueda.crea_arbol(raiz);
    agenda.push_back(0);
    while(!agenda.empty())
    {
        int nodo_actual = agenda[0];
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            arbol = arbol_de_busqueda;
            return true;
        }
        agenda.erase(agenda.begin());
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
            agenda.push_back(arbol_de_busqueda.devuelve_tamano_del_arbol() - 1);
        }
        ordena_por_costo_acumulado(agenda,arbol_de_busqueda,agenda.size());
    }
    return false;
}

bool Busqueda::beam_search(string nodo_inicio, string nodo_final, int& nodo_encontrado, int k)
{
    vector<int> agenda;
    Arbol arbol_de_busqueda;
    Nodo raiz_nodo;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    Nodo_informacion raiz;
    arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz);
    arbol_de_busqueda.crea_arbol(raiz);
    agenda.push_back(0);
    while(!agenda.empty())
    {
        int nodo_actual = agenda[0];
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            arbol = arbol_de_busqueda;
            return true;
        }
        agenda.erase(agenda.begin());
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
            agenda.push_back(arbol_de_busqueda.devuelve_tamano_del_arbol() - 1);
        }
        ordena_por_costo_acumulado(agenda,arbol_de_busqueda,k);
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
            if(temp_max.nombre == "" || raiz.costo_acumulado > temp_max.costo_acumulado)
            {
                temp_max = raiz;
            }
        }
        if(temp_max.nombre != "")
        {
            arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual, temp_max);
            max_num = new int(arbol_de_busqueda.devuelve_tamano_del_arbol() - 1);
        }
    }
    arbol = arbol_de_busqueda;
    return false;
}

bool Busqueda::branch_and_bound(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    vector<int> agenda;
    Arbol arbol_de_busqueda;
    Nodo raiz_nodo;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    Nodo_informacion raiz;
    arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz);
    arbol_de_busqueda.crea_arbol(raiz);
    agenda.push_back(0);
    while(!agenda.empty())
    {
        int nodo_actual = agenda[0];
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final && arbol_de_busqueda.devuelve_costo_acumulado_del_nodo(agenda[0]) <= arbol_de_busqueda.devuelve_costo_acumulado_del_nodo(nodo_encontrado))
        {
            nodo_encontrado = nodo_actual;
            arbol = arbol_de_busqueda;
            return true;
        }
        agenda.erase(agenda.begin());
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
            agenda.push_back(arbol_de_busqueda.devuelve_tamano_del_arbol() - 1);
        }
        ordena_por_costo_acumulado(agenda,arbol_de_busqueda,agenda.size());
    }
    return false;
}

bool Busqueda::es_costo_mas_heuristica_menor(vector<int>& agenda, float costo, Arbol& arbol) const
{
    for (auto i = agenda.begin(); i != agenda.end(); i++)
    {
        if (arbol.devuelve_costo_mas_heuristica_del_nodo(*i) < costo) return false;
    }
    return true;
}

void Busqueda::ordena_por_costo_mas_heuristica(vector<int>& agenda, Arbol& arbol)
{
    for (auto i = agenda.begin(); i != agenda.end(); i++)
    {
        for (auto j = agenda.begin(); j != agenda.end(); j++)
        {
            if (arbol.devuelve_costo_mas_heuristica_del_nodo(*i) < arbol.devuelve_costo_mas_heuristica_del_nodo(*j))
            {
                int temp = *i;
                *i = *j;
                *j = temp;
            }
        }
    }
}

bool Busqueda::busqueda_a_estrella(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    vector<int> agenda;
    Arbol arbol_de_busqueda;
    Nodo raiz_nodo;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    Nodo_informacion raiz;
    arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz);
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_final, raiz_nodo)) return false;
    float coordenada_x_final = raiz_nodo.coordenada_x;
    float coordenada_y_final = raiz_nodo.coordenada_y;
    arbol_de_busqueda.crea_arbol(raiz);
    agenda.push_back(0);
    while(!agenda.empty())
    {
        int nodo_actual = agenda[0];
        agenda.erase(agenda.begin());
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final && es_costo_mas_heuristica_menor(agenda, arbol_de_busqueda.devuelve_costo_mas_heuristica_del_nodo(nodo_actual), arbol_de_busqueda))
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
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            grafo.devuelve_informacion_de_un_nodo(i->nombre, raiz_nodo);
            arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(i->nombre, nodo_actual, raiz_nodo, raiz);
            raiz.costo_mas_heuristica = raiz.costo_acumulado + sqrt(pow(coordenada_x_final - raiz_nodo.coordenada_x, 2) + pow(coordenada_y_final - raiz_nodo.coordenada_y, 2));
            arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual, raiz);
            agenda.push_back(arbol_de_busqueda.devuelve_tamano_del_arbol() - 1);
        }
        ordena_por_costo_mas_heuristica(agenda,arbol_de_busqueda);
    }
    return false;
}
 
string Busqueda::devuelve_la_ruta_encontrada(int nodo_encontrado) const
{
    vector<int> temporal;
    string camino = "";
    temporal.clear();
    while (nodo_encontrado != -1)
    {
        temporal.push_back(nodo_encontrado);
        nodo_encontrado = arbol.devuelve_padre_de_un_nodo(nodo_encontrado);
    }
    for (int i = temporal.size() - 1; i >= 0; i--)
        camino = camino + " " + arbol.devuelve_nombre_de_un_nodo(temporal[i]);
    return camino;
}