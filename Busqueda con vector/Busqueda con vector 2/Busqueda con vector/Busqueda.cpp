#include "Busqueda.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
#include <stddef.h>

using namespace std;

#pragma warning(disable : 6011)

Busqueda::Busqueda()
{
    grafo.clear();
    arbol_de_busqueda.clear();
}

Busqueda::~Busqueda()
{

}

bool Busqueda::lee_grafo(string archivo)
{
    string leida;
    tipo_enlace_de_grafo enlace;
    fstream newfile;
    vector<string> vector_de_cadenas;
    grafo.clear();
    newfile.open(archivo, ios::in); 
    if (newfile.is_open()) 
    {  
        getline(newfile, leida);
        while (getline(newfile, leida)) 
        { 
            vector_de_cadenas.clear();
            stringstream cadena(leida);
            string temporal;
            while (getline(cadena, temporal, ','))
                vector_de_cadenas.push_back(temporal);
            enlace.nodo_1 = vector_de_cadenas[0];
            enlace.costo_nodo_1 = (float)atof(vector_de_cadenas[1].c_str());
            enlace.posicion_x_nodo_1 = (float)atof(vector_de_cadenas[2].c_str());
            enlace.posicion_y_nodo_1 = (float)atof(vector_de_cadenas[3].c_str());
            enlace.nodo_2 = vector_de_cadenas[4];
            enlace.costo_nodo_2 = (float)atof(vector_de_cadenas[5].c_str());
            enlace.posicion_x_nodo_2 = (float)atof(vector_de_cadenas[6].c_str());
            enlace.posicion_y_nodo_2 = (float)atof(vector_de_cadenas[7].c_str());
            enlace.costo_del_enlace = (float)atof(vector_de_cadenas[8].c_str());
            grafo.push_back(enlace);
        }
        newfile.close();
        return true;
    }
    else
        return false;
}

void Busqueda::devuelve_vecinos_grafo_no_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const
{
    vecinos.clear();
    tipo_enlace_de_grafo temporal;
    for (size_t i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo_1 == nodo)
            vecinos.push_back(grafo[i]);
        else if (grafo[i].nodo_2 == nodo)
        {
            temporal.nodo_1 = grafo[i].nodo_2;
            temporal.costo_nodo_1 = grafo[i].costo_nodo_2;
            temporal.posicion_x_nodo_1 = grafo[i].posicion_x_nodo_2;
            temporal.posicion_y_nodo_1 = grafo[i].posicion_y_nodo_2;
            temporal.nodo_2 = grafo[i].nodo_1;
            temporal.costo_nodo_2 = grafo[i].costo_nodo_1;
            temporal.posicion_x_nodo_2 = grafo[i].posicion_x_nodo_1;
            temporal.posicion_y_nodo_2 = grafo[i].posicion_y_nodo_1;
            temporal.costo_del_enlace = grafo[i].costo_del_enlace;
            vecinos.push_back(temporal);
        }
            
}

bool Busqueda::devuelve_informacion_de_un_vertice_grafo_no_dirigido(string nodo, int nodo_padre, tipo_nodo_informacion& informacion) const
{
    float costo_acumulado_del_padre = 0.0f;
    string nombre_del_nodo_padre = "";
    if (nodo_padre != -1)
    {
        costo_acumulado_del_padre = arbol_de_busqueda[nodo_padre].contenido.costo_acumulado;
        nombre_del_nodo_padre = arbol_de_busqueda[nodo_padre].contenido.nombre_del_nodo;
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_1 == nodo &&
                grafo[i].nodo_2 == nombre_del_nodo_padre)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_1;
                informacion.costo_acumulado = grafo[i].costo_nodo_1 +
                    costo_acumulado_del_padre +
                    grafo[i].costo_del_enlace;
                return true;
            }
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_2 == nodo &&
                grafo[i].nodo_1 == nombre_del_nodo_padre)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_2;
                informacion.costo_acumulado = grafo[i].costo_nodo_2 +
                    costo_acumulado_del_padre +
                    grafo[i].costo_del_enlace;
                return true;
            }
        return false;
    }
    else
    {
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_1 == nodo)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_1;
                informacion.costo_acumulado = grafo[i].costo_nodo_1;
                return true;
            }
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_2 == nodo)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_2;
                informacion.costo_acumulado = grafo[i].costo_nodo_2;
                return true;
            }
        return false;
    }
}

bool Busqueda::devuelve_informacion_de_un_vertice_grafo_no_dirigido_busqueda_bidireccional(string nodo, int nodo_padre, tipo_nodo_informacion& informacion, vector<tipo_nodo_del_arbol>& arbol) const
{
    float costo_acumulado_del_padre = 0.0f;
    string nombre_del_nodo_padre = "";
    if (nodo_padre != -1)
    {
        costo_acumulado_del_padre = arbol[nodo_padre].contenido.costo_acumulado;
        nombre_del_nodo_padre = arbol[nodo_padre].contenido.nombre_del_nodo;
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_1 == nodo &&
                grafo[i].nodo_2 == nombre_del_nodo_padre)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_1;
                informacion.costo_acumulado = grafo[i].costo_nodo_1 +
                    costo_acumulado_del_padre +
                    grafo[i].costo_del_enlace;
                return true;
            }
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_2 == nodo &&
                grafo[i].nodo_1 == nombre_del_nodo_padre)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_2;
                informacion.costo_acumulado = grafo[i].costo_nodo_2 +
                    costo_acumulado_del_padre +
                    grafo[i].costo_del_enlace;
                return true;
            }
        return false;
    }
    else
    {
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_1 == nodo)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_1;
                informacion.costo_acumulado = grafo[i].costo_nodo_1;
                return true;
            }
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_2 == nodo)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_2;
                informacion.costo_acumulado = grafo[i].costo_nodo_2;
                return true;
            }
        return false;
    }
}

void Busqueda::crea_arbol(tipo_nodo_informacion contenido)
{
    tipo_nodo_del_arbol temporal;
    temporal.padre = -1;
    temporal.contenido = contenido;
    temporal.hijos.clear();
    arbol_de_busqueda.push_back(temporal);
 }

void Busqueda::agrega_hijo_a_un_nodo(int padre, tipo_nodo_informacion contenido)
{
    tipo_nodo_del_arbol temporal;
    temporal.padre = padre;
    temporal.contenido = contenido;
    temporal.hijos.clear();
    arbol_de_busqueda.push_back(temporal);
    arbol_de_busqueda[padre].hijos.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
}

void Busqueda::agrega_hijo_a_un_nodo_busqueda_bidireccional(int padre, tipo_nodo_informacion contenido, vector<tipo_nodo_del_arbol>& arbol)
{
    tipo_nodo_del_arbol temporal;
    temporal.padre = padre;
    temporal.contenido = contenido;
    temporal.hijos.clear();
    arbol.push_back(temporal);
    arbol[padre].hijos.push_back((unsigned int)(arbol.size() - 1));
}

bool Busqueda::esta_un_nodo_en_ancestros(const int nodo_origen, string nombre_del_nodo) const
{
    int temporal = arbol_de_busqueda[nodo_origen].padre;
    while (temporal != -1)
    {
        if (arbol_de_busqueda[temporal].contenido.nombre_del_nodo == nombre_del_nodo)
            return true;
        temporal = arbol_de_busqueda[temporal].padre;
    } 
    return false;
}

bool Busqueda::busqueda_primero_en_profundidad(string nodo_inicio, string nodo_final, int & nodo_encontrado)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    int temporal = 0;
    int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio);
    Agenda.push_back(0);
    while (!Agenda.empty())
    {
        nodo_actual = Agenda.front();
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        Agenda.erase(Agenda.begin());
        devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, nodo_actual, informacion_del_hijo_a_adicionar);
            agrega_hijo_a_un_nodo(nodo_actual, informacion_del_hijo_a_adicionar);
            Agenda.insert(Agenda.begin(), (unsigned int)(arbol_de_busqueda.size() - 1));
        }
    }
    return false;
}

bool Busqueda::dfs(vector<int>& agenda, vector<tipo_nodo_del_arbol>& arbol, string nodo_final, int& nodo_encontrado)
{
    int nodo_actual = agenda.front();
    vector<tipo_enlace_de_grafo> vecinos;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    if (arbol[nodo_actual].contenido.nombre_del_nodo == nodo_final)
    {
        nodo_encontrado = nodo_actual;
        return true;
    }
    agenda.erase(agenda.begin());
    devuelve_vecinos_grafo_no_dirigido(arbol[nodo_actual].contenido.nombre_del_nodo, vecinos);
    for(unsigned int i = 0; i < vecinos.size(); i++){
        int temporal = arbol[nodo_actual].padre;
        while (temporal != -1)
        {
            if (arbol[temporal].contenido.nombre_del_nodo == vecinos[i].nodo_2)
                vecinos.erase(vecinos.begin() + i);
                i--;
                break;
            temporal = arbol[temporal].padre;
        } 
    }
    for (unsigned int i = 0; i < vecinos.size(); i++)
    {
        devuelve_informacion_de_un_vertice_grafo_no_dirigido_busqueda_bidireccional(vecinos[i].nodo_2, nodo_actual, informacion_del_hijo_a_adicionar, arbol);
        agrega_hijo_a_un_nodo_busqueda_bidireccional(nodo_actual, informacion_del_hijo_a_adicionar, arbol);
        agenda.insert(agenda.begin(), (unsigned int)(arbol.size() - 1));
    }
    return false;
}

bool Busqueda::busqueda_primero_en_profundidad_limitada(string nodo_inicio, string nodo_final, int & nodo_encontrado, int profundidad)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    int temporal = 0;
    int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio);
    Agenda.push_back(0);
    while (!Agenda.empty())
    {
        nodo_actual = Agenda.front();
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        if(arbol_de_busqueda[nodo_actual].contenido.profundidad == profundidad)
        {
            Agenda.erase(Agenda.begin());
            continue;
        }
        Agenda.erase(Agenda.begin());
        devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, nodo_actual, informacion_del_hijo_a_adicionar);
            informacion_del_hijo_a_adicionar.profundidad = arbol_de_busqueda[nodo_actual].contenido.profundidad + 1;
            agrega_hijo_a_un_nodo(nodo_actual, informacion_del_hijo_a_adicionar);
            Agenda.insert(Agenda.begin(), (unsigned int)(arbol_de_busqueda.size() - 1));
        }
    }
    return false;
}

bool Busqueda::busqueda_primero_en_profundidad_iterativa(string nodo_inicio, string nodo_final, int & nodo_encontrado)
{
    int profundidad = 0;
    while (!busqueda_primero_en_profundidad_limitada(nodo_inicio, nodo_final, nodo_encontrado, profundidad))
    {
        profundidad++;
    }
    return false;
}

bool Busqueda::busqueda_a_lo_ancho(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    int temporal = 0;
    int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio);
    Agenda.push_back(0);
    while (!Agenda.empty())
    {
        nodo_actual = Agenda.front();
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        Agenda.erase(Agenda.begin());
        devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, nodo_actual, informacion_del_hijo_a_adicionar);
            agrega_hijo_a_un_nodo(nodo_actual, informacion_del_hijo_a_adicionar);
            Agenda.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
        }
    }
    return false;
}

bool Busqueda::bfs(vector<int>& agenda, vector<tipo_nodo_del_arbol>& arbol, string nodo_final, int& nodo_encontrado)
{
    int nodo_actual = agenda.front();
    vector<tipo_enlace_de_grafo> vecinos;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    if (arbol[nodo_actual].contenido.nombre_del_nodo == nodo_final)
    {
        nodo_encontrado = nodo_actual;
        return true;
    }
    agenda.erase(agenda.begin());
    devuelve_vecinos_grafo_no_dirigido(arbol[nodo_actual].contenido.nombre_del_nodo, vecinos);
    for(unsigned int i = 0; i < vecinos.size(); i++){
        int temporal = arbol[nodo_actual].padre;
        while (temporal != -1)
        {
            if (arbol[temporal].contenido.nombre_del_nodo == vecinos[i].nodo_2)
                vecinos.erase(vecinos.begin() + i);
                i--;
                break;
            temporal = arbol[temporal].padre;
        } 
    }
    for (unsigned int i = 0; i < vecinos.size(); i++)
    {
        devuelve_informacion_de_un_vertice_grafo_no_dirigido_busqueda_bidireccional(vecinos[i].nodo_2, nodo_actual, informacion_del_hijo_a_adicionar, arbol);
        agrega_hijo_a_un_nodo_busqueda_bidireccional(nodo_actual, informacion_del_hijo_a_adicionar, arbol);
        agenda.push_back((unsigned int)(arbol.size() - 1));
    }
    return false;
}

bool Busqueda::intersecta(vector<tipo_nodo_del_arbol>& arbol_1, vector<tipo_nodo_del_arbol>& arbol_2, int& nodo_1, int& nodo_2)
{
    for (unsigned int i = 0; i < arbol_1.size(); i++)
        for (unsigned int j = 0; j < arbol_2.size(); j++)
            if (arbol_1[i].contenido.nombre_del_nodo == arbol_2[j].contenido.nombre_del_nodo)
            {
                nodo_1 = i;
                nodo_2 = j;
                return true;
            }
    return false;
}

bool Busqueda::busqueda_bidireccional(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    vector<int> agenda_1;
    vector<int> agenda_2;
    vector<tipo_nodo_del_arbol> arbol_1;
    vector<tipo_nodo_del_arbol> arbol_2;
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    int nodo_1 = 0;
    int nodo_2 = 0;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, -1, informacion_del_nodo_inicio))
        return false;
    tipo_nodo_del_arbol temporal;
    temporal.padre = -1;
    temporal.contenido = informacion_del_nodo_inicio;
    temporal.hijos.clear(); 
    arbol_1.push_back(temporal);
    if(!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_final, -1, informacion_del_nodo_inicio))
        return false;
    temporal.padre = -1;
    temporal.contenido = informacion_del_nodo_inicio;
    temporal.hijos.clear();
    arbol_2.push_back(temporal);
    agenda_1.push_back(0);
    agenda_2.push_back(0);
    while (!agenda_1.empty() && !agenda_2.empty())
    {
        if (bfs(agenda_1, arbol_1, nodo_final, nodo_1))
        {
            nodo_encontrado = nodo_1;
            return true;
        }
        if (dfs(agenda_2, arbol_2, nodo_inicio, nodo_2))
        {
            nodo_encontrado = nodo_2;
            return true;
        }
        if (intersecta(arbol_1, arbol_2, nodo_1, nodo_2))
        {
            cout << nodo_1 << endl;
            cout << nodo_2 << endl;
            nodo_encontrado = nodo_1;
            return true;
        }
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
        nodo_encontrado = arbol_de_busqueda[nodo_encontrado].padre;
    }
    for (int i = (int)(temporal.size() - 1); i >= 0; i--)
        camino = camino + " " + arbol_de_busqueda[temporal[i]].contenido.nombre_del_nodo;
    return camino;
}


