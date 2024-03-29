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
        if(int(cola.size()) > max_agenda) max_agenda = cola.size();
        if(arbol_de_busqueda.devuelve_tamano_del_arbol() > max_arbol) max_arbol = arbol_de_busqueda.devuelve_tamano_del_arbol();
        int nodo_actual = cola.front();
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            arbol = arbol_de_busqueda;
            return true;
        }
        cola.pop();
        unordered_map<string, float> vecinos = grafo.devuelve_vecinos_de_un_nodo(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual));
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            if(arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, i->first)) continue;
            grafo.devuelve_informacion_de_un_nodo(i->first, raiz_nodo);
            arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(i->first, nodo_actual, raiz_nodo, raiz);
            arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual, raiz);
            cola.push(arbol_de_busqueda.devuelve_tamano_del_arbol() - 1);
        }
    }
    return false;
}

bool Busqueda::intersectan(deque<int>& camino_inicio, deque<int>& camino_final, int& nodo_encontrado_inicio, int& nodo_encontrado_final, Arbol& arbol_de_busqueda_inicio, Arbol& arbol_de_busqueda_final)
{
    for(auto i = camino_inicio.begin(); i != camino_inicio.end(); i++)
    {
        for(auto j = camino_final.begin(); j != camino_final.end(); j++)
        {
            if(arbol_de_busqueda_inicio.devuelve_nombre_de_un_nodo(*i) == arbol_de_busqueda_final.devuelve_nombre_de_un_nodo(*j))
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
        if(int(camino_inicio.size()) > max_agenda) max_agenda = camino_inicio.size();
        if(arbol_de_busqueda_inicio.devuelve_tamano_del_arbol() > max_arbol) max_arbol = arbol_de_busqueda_inicio.devuelve_tamano_del_arbol();
        int nodo_actual = camino_inicio.front();
        if(arbol_de_busqueda_inicio.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado_inicio = nodo_actual;
            arbol = arbol_de_busqueda_inicio;
            return true;
        }
        camino_inicio.pop_front();
        unordered_map<string, float> vecinos = grafo.devuelve_vecinos_de_un_nodo(arbol_de_busqueda_inicio.devuelve_nombre_de_un_nodo(nodo_actual));
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            if(arbol_de_busqueda_inicio.esta_un_nodo_en_ancestros(nodo_actual, i->first)) continue;
            grafo.devuelve_informacion_de_un_nodo(i->first, raiz_nodo);
            arbol_de_busqueda_inicio.devuelve_informacion_de_un_vertice_grafo_no_dirigido(i->first, nodo_actual, raiz_nodo, raiz);
            arbol_de_busqueda_inicio.agrega_hijo_a_un_nodo(nodo_actual, raiz);
            camino_inicio.push_back(arbol_de_busqueda_inicio.devuelve_tamano_del_arbol() - 1);
        }
        if(int(camino_final.size()) > max_agenda) max_agenda = camino_final.size();
        if(arbol_de_busqueda_final.devuelve_tamano_del_arbol() > max_arbol) max_arbol = arbol_de_busqueda_final.devuelve_tamano_del_arbol();
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
            if(arbol_de_busqueda_final.esta_un_nodo_en_ancestros(nodo_actual, i->first)) continue;
            grafo.devuelve_informacion_de_un_nodo(i->first, raiz_nodo);
            arbol_de_busqueda_final.devuelve_informacion_de_un_vertice_grafo_no_dirigido(i->first, nodo_actual, raiz_nodo, raiz);
            arbol_de_busqueda_final.agrega_hijo_a_un_nodo(nodo_actual, raiz);
            camino_final.push_front(arbol_de_busqueda_final.devuelve_tamano_del_arbol() - 1);
        }
        if(intersectan(camino_inicio, camino_final, nodo_encontrado_inicio, nodo_encontrado_final, arbol_de_busqueda_inicio, arbol_de_busqueda_final))
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
    Nodo_informacion raiz;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz);
    arbol_de_busqueda.crea_arbol(raiz);
    pila.push(0);
    while(!pila.empty())
    {
        if(int(pila.size()) > max_agenda) max_agenda = pila.size();
        if(arbol_de_busqueda.devuelve_tamano_del_arbol() > max_arbol) max_arbol = arbol_de_busqueda.devuelve_tamano_del_arbol();
        int nodo_actual = pila.top();
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            arbol = arbol_de_busqueda;
            return true;
        }
        pila.pop();
        unordered_map<string, float> vecinos = grafo.devuelve_vecinos_de_un_nodo(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual));
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            if(arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, i->first)) continue;
            grafo.devuelve_informacion_de_un_nodo(i->first, raiz_nodo);
            arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(i->first, nodo_actual, raiz_nodo, raiz);
            arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual, raiz);
            pila.push(arbol_de_busqueda.devuelve_tamano_del_arbol() - 1);
        }
    }
    return false;
}

bool Busqueda::busqueda_primero_en_profundidad_limitada(string nodo_inicio, string nodo_final, int& nodo_encontrado, int limite)
{
    stack<int> pila;
    Arbol arbol_de_busqueda;
    Nodo raiz_nodo;
    Nodo_informacion raiz;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz);
    arbol_de_busqueda.crea_arbol(raiz);
    pila.push(0);
    while(!pila.empty())
    {
        if(int(pila.size()) > max_agenda) max_agenda = pila.size();
        if(arbol_de_busqueda.devuelve_tamano_del_arbol() > max_arbol) max_arbol = arbol_de_busqueda.devuelve_tamano_del_arbol();
        int nodo_actual = pila.top();
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            arbol = arbol_de_busqueda;
            return true;
        }
        pila.pop();
        unordered_map<string, float> vecinos;
        if(arbol_de_busqueda.devuelve_profundidad_del_nodo(arbol_de_busqueda.devuelve_tamano_del_arbol() - 1) <= limite)
            vecinos = grafo.devuelve_vecinos_de_un_nodo(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual));
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            if(arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, i->first)) continue;
            grafo.devuelve_informacion_de_un_nodo(i->first, raiz_nodo);
            arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(i->first, nodo_actual, raiz_nodo, raiz);
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
    if(k < agenda.size())
        agenda.erase(agenda.begin() + k, agenda.end());
}

bool Busqueda::busqueda_primero_el_mejor(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    arbol = Arbol();
    auto compare = [&,this](int lhs, int rhs)
    {
        return this->arbol.devuelve_costo_acumulado_del_nodo(lhs) > this->arbol.devuelve_costo_acumulado_del_nodo(rhs);
    };

    priority_queue<int, vector<int>,decltype(compare)> agenda (compare);

    Nodo raiz_nodo;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    Nodo_informacion raiz;
    arbol.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz);
    arbol.crea_arbol(raiz);
    agenda.push(0);
    while(!agenda.empty())
    {
        if(int(agenda.size()) > max_agenda) max_agenda = agenda.size();
        if(arbol.devuelve_tamano_del_arbol() > max_arbol) max_arbol = arbol.devuelve_tamano_del_arbol();
        int nodo_actual = agenda.top();
        if(arbol.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        agenda.pop();
        unordered_map<string, float> vecinos = grafo.devuelve_vecinos_de_un_nodo(arbol.devuelve_nombre_de_un_nodo(nodo_actual));
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            if(arbol.esta_un_nodo_en_ancestros(nodo_actual, i->first)) continue;
            grafo.devuelve_informacion_de_un_nodo(i->first, raiz_nodo);
            arbol.devuelve_informacion_de_un_vertice_grafo_no_dirigido(i->first, nodo_actual, raiz_nodo, raiz);
            arbol.agrega_hijo_a_un_nodo(nodo_actual, raiz);
            agenda.push(arbol.devuelve_tamano_del_arbol() - 1);
        }
    }
    return false;
}

bool Busqueda::beam_search(string nodo_inicio, string nodo_final, int& nodo_encontrado, int k)
{
    arbol = Arbol();
    vector<int> agenda;   
    Nodo raiz_nodo;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    Nodo_informacion raiz;
    arbol.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz);
    arbol.crea_arbol(raiz);
    agenda.push_back(0);
    while(!agenda.empty())
    {
        if(int(agenda.size()) > max_agenda) max_agenda = agenda.size();
        if(arbol.devuelve_tamano_del_arbol() > max_arbol) max_arbol = arbol.devuelve_tamano_del_arbol();
        int nodo_actual = agenda[0];
        if(arbol.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        agenda.erase(agenda.begin());
        unordered_map<string, float> vecinos = grafo.devuelve_vecinos_de_un_nodo(arbol.devuelve_nombre_de_un_nodo(nodo_actual));

        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            if(arbol.esta_un_nodo_en_ancestros(nodo_actual, i->first)) continue;
            grafo.devuelve_informacion_de_un_nodo(i->first, raiz_nodo);
            arbol.devuelve_informacion_de_un_vertice_grafo_no_dirigido(i->first, nodo_actual, raiz_nodo, raiz);
            arbol.agrega_hijo_a_un_nodo(nodo_actual, raiz);
            agenda.push_back(arbol.devuelve_tamano_del_arbol() - 1);
        }
        ordena_por_costo_acumulado(agenda, arbol, k);
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
    max_agenda = 1;
    while(max_num != NULL)
    {
        if(arbol_de_busqueda.devuelve_tamano_del_arbol() > max_arbol) max_arbol = arbol_de_busqueda.devuelve_tamano_del_arbol();
        int nodo_actual = *max_num;
        max_num = NULL;
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            arbol = arbol_de_busqueda;
            return true;
        }
        unordered_map<string, float> vecinos = grafo.devuelve_vecinos_de_un_nodo(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual));
        Nodo_informacion temp_max;
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            if(arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, i->first)) continue;
            grafo.devuelve_informacion_de_un_nodo(i->first, raiz_nodo);
            arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(i->first, nodo_actual, raiz_nodo, raiz);
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
    int mejor_solucion = -1;
    Arbol arbol_de_busqueda;
    Nodo raiz_nodo;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    Nodo_informacion raiz;
    arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz);
    arbol_de_busqueda.crea_arbol(raiz);
    agenda.push_back(0);
    while(!agenda.empty())
    {
        if(int(agenda.size()) > max_agenda) max_agenda = agenda.size();
        if(arbol_de_busqueda.devuelve_tamano_del_arbol() > max_arbol) max_arbol = arbol_de_busqueda.devuelve_tamano_del_arbol();
        int nodo_actual = agenda[0];
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            
            mejor_solucion = nodo_actual;
            while(!agenda.empty() && arbol_de_busqueda.devuelve_costo_acumulado_del_nodo(agenda[agenda.size()-1]) >= arbol_de_busqueda.devuelve_costo_acumulado_del_nodo(mejor_solucion))
            {
                agenda.erase(agenda.begin() + agenda.size() - 1);
            }
            if(agenda.empty()){
                arbol = arbol_de_busqueda;
                nodo_encontrado = mejor_solucion;
                return true;
            }
        }
        agenda.erase(agenda.begin());
        unordered_map<string, float> vecinos = grafo.devuelve_vecinos_de_un_nodo(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual));

        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            if(arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, i->first)) continue;
            grafo.devuelve_informacion_de_un_nodo(i->first, raiz_nodo);
            arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(i->first, nodo_actual, raiz_nodo, raiz);
            arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual, raiz);
            if(mejor_solucion == -1 || raiz.costo_acumulado < arbol_de_busqueda.devuelve_costo_acumulado_del_nodo(mejor_solucion))
            {
                agenda.push_back(arbol_de_busqueda.devuelve_tamano_del_arbol() - 1);
            }
        }
        sort(agenda.begin(), agenda.end(), [this, &arbol_de_busqueda](int a, int b){return arbol_de_busqueda.devuelve_costo_acumulado_del_nodo(a) < arbol_de_busqueda.devuelve_costo_acumulado_del_nodo(b);});
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
    int meta_temporal = -1;
    int posicion_mejor;
    vector<int> agenda;
    Arbol arbol_de_busqueda;
    Nodo raiz_nodo;
    Nodo meta_nodo;
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_inicio, raiz_nodo)) return false;
    Nodo_informacion raiz;
    arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz_nodo, raiz);
    if(!grafo.devuelve_informacion_de_un_nodo(nodo_final, meta_nodo)) return false;
    float coordenada_x_final = meta_nodo.coordenada_x;
    float coordenada_y_final = meta_nodo.coordenada_y;
    raiz.costo_mas_heuristica = raiz.costo_acumulado + (float)sqrt(pow(coordenada_x_final - raiz_nodo.coordenada_x, 2) + pow(coordenada_y_final - raiz_nodo.coordenada_y, 2));
    arbol_de_busqueda.crea_arbol(raiz);
    agenda.push_back(0);
    while(!agenda.empty())
    {
        if(int(agenda.size()) > max_agenda) max_agenda = agenda.size();
        if(arbol_de_busqueda.devuelve_tamano_del_arbol() > max_arbol) max_arbol = arbol_de_busqueda.devuelve_tamano_del_arbol();
        int nodo_actual = agenda[0];
        posicion_mejor = 0;
        auto costo_del_mejor = arbol_de_busqueda.devuelve_costo_mas_heuristica_del_nodo(nodo_actual);
        for(unsigned int i = 1; i < agenda.size(); i++)
        {
            if(costo_del_mejor > arbol_de_busqueda.devuelve_costo_mas_heuristica_del_nodo(agenda[i]))
            {
                nodo_actual = agenda[i];
                posicion_mejor = i;
                costo_del_mejor = arbol_de_busqueda.devuelve_costo_mas_heuristica_del_nodo(nodo_actual);
            }
        }
        agenda.erase(agenda.begin() + posicion_mejor);
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            if(meta_temporal == -1) meta_temporal = nodo_actual;
            else if(arbol_de_busqueda.devuelve_costo_acumulado_del_nodo(nodo_actual) < arbol_de_busqueda.devuelve_costo_acumulado_del_nodo(meta_temporal)) meta_temporal = nodo_actual;
            for(unsigned int i = 0; i < agenda.size(); i++)
            {
                if(arbol_de_busqueda.devuelve_costo_acumulado_del_nodo(agenda[i]) >= arbol_de_busqueda.devuelve_costo_acumulado_del_nodo(meta_temporal)) {
                    agenda.erase(agenda.begin() + i);
                    i--;
                }
            }
            if(agenda.empty())
            {
                nodo_encontrado = meta_temporal;
                return true;
            }
        }
        unordered_map<string, float> vecinos = grafo.devuelve_vecinos_de_un_nodo(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual));
        for(auto i = vecinos.begin(); i != vecinos.end(); i++)
        {
            if(arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, i->first)) continue;
            grafo.devuelve_informacion_de_un_nodo(i->first, raiz_nodo);
            arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(i->first, nodo_actual, raiz_nodo, raiz);
            raiz.costo_mas_heuristica = raiz.costo_acumulado + (float)sqrt(pow(coordenada_x_final - raiz_nodo.coordenada_x, 2) + pow(coordenada_y_final - raiz_nodo.coordenada_y, 2));
            if(meta_temporal != -1 && arbol_de_busqueda.devuelve_costo_acumulado_del_nodo(meta_temporal) < raiz.costo_acumulado) continue;
            arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual, raiz);
            agenda.push_back(arbol_de_busqueda.devuelve_tamano_del_arbol() - 1);
        }
    }
    nodo_encontrado = meta_temporal;
    arbol = arbol_de_busqueda;
    return meta_temporal != -1;
}
 
string Busqueda::devuelve_la_ruta_encontrada(int nodo_encontrado,int& costo) const
{
    vector<int> temporal;
    string camino = "";
    temporal.clear();
    costo = arbol.devuelve_costo_acumulado_del_nodo(nodo_encontrado);
    while (nodo_encontrado != -1)
    {
        temporal.push_back(nodo_encontrado);
        nodo_encontrado = arbol.devuelve_padre_de_un_nodo(nodo_encontrado);
    }
    for (int i =(int)temporal.size() - 1; i >= 0; i--)
        camino = camino + " - " + arbol.devuelve_nombre_de_un_nodo(temporal[i]);
    return camino;
}

string Busqueda::devuelve_la_ruta_bidireccional(int nodo_encontrado, int nodo_encontrado2) const
{
    vector<string> temporal;
    string camino = "";
    cout << "Ruta encontrada: ";
    while (nodo_encontrado != -1)
    {
        temporal.push_back(arbol.devuelve_nombre_de_un_nodo(nodo_encontrado));
        nodo_encontrado = arbol.devuelve_padre_de_un_nodo(nodo_encontrado);
    }
    reverse(temporal.begin(), temporal.end());
    nodo_encontrado2 = arbol_final.devuelve_padre_de_un_nodo(nodo_encontrado2);
    while (nodo_encontrado2 != -1)
    {
        temporal.push_back(arbol_final.devuelve_nombre_de_un_nodo(nodo_encontrado2));
        nodo_encontrado2 = arbol_final.devuelve_padre_de_un_nodo(nodo_encontrado2);
    }
    for(auto i = temporal.begin(); i != temporal.end(); i++)
        camino = camino + " - " + *i;
    return camino;
}

string Busqueda::devuelve_max_agenda() const
{
    return to_string(max_agenda);
}

string Busqueda::devuelve_max_arbol() const
{
    return to_string(max_arbol);
}

void Busqueda::reset_max()
{
    max_agenda = -1;
    max_arbol = -1;
}