#include "Busqueda.h"

Busqueda::Busqueda()
{
}

bool Busqueda::best_first(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    auto compare = [&,this](int lhs, int rhs)
    {
        return this->arbol_de_busqueda.devuelve_heuristica(lhs) > this->arbol_de_busqueda.devuelve_heuristica(rhs);
    };

    priority_queue<int, vector<int>, decltype(compare)> cola (compare);
    Arbol arbol(nodo_final);
    arbol_de_busqueda = arbol;
    Nodo_informacion raiz;
    arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz);
    arbol_de_busqueda.crea_arbol(raiz);
    cola.push(0);
    while(!cola.empty())
    {
        //cout << "cola: " << cola.top() << endl;
        int nodo_actual = cola.top();
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        cola.pop();
        vector<string> vecinos = arbol_de_busqueda.devuelve_vecinos_de_un_nodo(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual));
        for(int i =0; i < vecinos.size(); i++)
        {
            if(arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual,vecinos[i])) continue;
            arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i], nodo_actual, raiz);
            arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual, raiz);
            cola.push(arbol_de_busqueda.devuelve_tamano_del_arbol() - 1);
        }
    }
    return false;
}

/*bool Busqueda::branch_and_bound(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    vector<int> agenda;
    int mejor_solucion = -1;
    Arbol arbol_de_busqueda(nodo_final);
    Nodo_informacion raiz;
    arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, raiz);
    arbol_de_busqueda.crea_arbol(raiz);
    agenda.push_back(0);
    while(!agenda.empty())
    {
        int nodo_actual = agenda[0];
        if(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual) == nodo_final)
        {
            
            mejor_solucion = nodo_actual;
            while(!agenda.empty() && arbol_de_busqueda.devuelve_profundidad_del_nodo(agenda[agenda.size()-1]) >= arbol_de_busqueda.devuelve_profundidad_del_nodo(mejor_solucion))
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
        vector<string> vecinos = arbol_de_busqueda.devuelve_vecinos_de_un_nodo(arbol_de_busqueda.devuelve_nombre_de_un_nodo(nodo_actual));

        for(int i =0; i < vecinos.size(); i++)
        {
            if(arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i])) continue;
            arbol_de_busqueda.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i], nodo_actual,  raiz);
            arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual, raiz);
            if(raiz.costo_acumulado < arbol_de_busqueda.devuelve_costo_acumulado_del_nodo(mejor_solucion) || mejor_solucion == -1)
            {
                agenda.push_back(arbol_de_busqueda.devuelve_tamano_del_arbol() - 1);
            }
        }
        sort(agenda.begin(), agenda.end(), [this, &arbol_de_busqueda](int a, int b){return arbol_de_busqueda.devuelve_heuristica(a) < arbol_de_busqueda.devuelve_heuristica(b);});
    }
    return false;
}*/

string Busqueda::devuelve_la_ruta_encontrada(int nodo_encontrado) const
{
    vector<int> temporal;
    string camino = "";
    temporal.clear();
    while (nodo_encontrado != -1)
    {
        temporal.push_back(nodo_encontrado);
        nodo_encontrado = arbol_de_busqueda.devuelve_padre_de_un_nodo(nodo_encontrado);
    }
    for (int i =(int)temporal.size() - 1; i >= 0; i--)
    {
        camino = camino + "\n\n";
        for(int j = 1; j <= arbol_de_busqueda.devuelve_nombre_de_un_nodo(i).size(); j++)
        {
            camino = camino + arbol_de_busqueda.devuelve_nombre_de_un_nodo(temporal[i])[j-1] + " ";
            if (j%5==0)
            {
                camino = camino + "\n";
            }
            
        }
    }
    return camino;
}