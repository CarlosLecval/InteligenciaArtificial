#include "Busqueda.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
#include <stddef.h>
#include <cmath>

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

bool Busqueda::devuelve_informacion_de_un_vertice_grafo_no_dirigido(string nodo, vector<tipo_nodo_del_arbol> arbol,
                                                        int nodo_padre, tipo_nodo_informacion& informacion) const
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

void Busqueda::crea_arbol(tipo_nodo_informacion contenido, vector<tipo_nodo_del_arbol>& arbol_creado)
{
    tipo_nodo_del_arbol temporal;
    temporal.padre = -1;
    temporal.profundidad = 0;
    temporal.contenido = contenido;
    temporal.hijos.clear();
    arbol_creado.clear();
    arbol_creado.push_back(temporal);
 }

void Busqueda::agrega_hijo_a_un_nodo(vector<tipo_nodo_del_arbol>& arbol, int padre, tipo_nodo_informacion contenido)
{
    tipo_nodo_del_arbol temporal;
    temporal.padre = padre;
    temporal.profundidad = arbol[padre].profundidad + 1;
    temporal.contenido = contenido;
    temporal.hijos.clear();
    arbol.push_back(temporal);
    arbol[padre].hijos.push_back((unsigned int)(arbol.size() - 1));
}

bool Busqueda::esta_un_nodo_en_ancestros(vector<tipo_nodo_del_arbol> arbol, const int nodo_origen, string nombre_del_nodo) const
{
    int temporal = arbol[nodo_origen].padre;
    while (temporal != -1)
    {
        if (arbol[temporal].contenido.nombre_del_nodo == nombre_del_nodo)
            return true;
        temporal = arbol[temporal].padre;
    } 
    return false;
}

bool Busqueda::busqueda_primero_en_profundidad(string nodo_inicio, string nodo_final, int & nodo_encontrado)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda, -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    Agenda.clear();
    Agenda.push_back(0);
    while (!Agenda.empty())
    {
        nodo_actual = Agenda.front();
        Agenda.erase(Agenda.begin());
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, 
                                            arbol_de_busqueda, nodo_actual, 
                                            informacion_del_hijo_a_adicionar);
            agrega_hijo_a_un_nodo(arbol_de_busqueda, nodo_actual,
                                        informacion_del_hijo_a_adicionar);
            Agenda.insert(Agenda.begin(), (unsigned int)(arbol_de_busqueda.size() - 1));
        }
    }
    return false;
}

bool Busqueda::busqueda_tinmarin(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda, 
                                                            -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    Agenda.clear();
    Agenda.push_back(0);
    while (!Agenda.empty())
    {
        nodo_actual = Agenda[Agenda.size()/2];
        Agenda.erase(Agenda.begin() + Agenda.size()/2);
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, arbol_de_busqueda, 
                                                            nodo_actual, informacion_del_hijo_a_adicionar);
            agrega_hijo_a_un_nodo(arbol_de_busqueda, nodo_actual, informacion_del_hijo_a_adicionar);
            if(i % 2 == 0) Agenda.insert(Agenda.begin(), (unsigned int)(arbol_de_busqueda.size() - 1));
            else Agenda.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
        }
    }
    return false;
}

bool Busqueda::busqueda_a_lo_ancho(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda, 
                                                            -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    Agenda.clear();
    Agenda.push_back(0);
    while (!Agenda.empty())
    {
        nodo_actual = Agenda.front();
        Agenda.erase(Agenda.begin());
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, arbol_de_busqueda, 
                                                            nodo_actual, informacion_del_hijo_a_adicionar);
            agrega_hijo_a_un_nodo(arbol_de_busqueda, nodo_actual, informacion_del_hijo_a_adicionar);
            Agenda.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
        }
    }
    return false;
}
bool Busqueda::busqueda_profundidad_limitada(string nodo_inicio, string nodo_final,
                                    unsigned int limite_de_profundidad, int& nodo_encontrado)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda , 
                                                               -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    Agenda.clear();
    Agenda.push_back(0);
    while (!Agenda.empty())
    {
        nodo_actual = Agenda.front();
        Agenda.erase(Agenda.begin());
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        if (arbol_de_busqueda[nodo_actual].profundidad < limite_de_profundidad)
        {
            devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
            for (unsigned int i = 0; i < vecinos.size(); i++)
                if (esta_un_nodo_en_ancestros(arbol_de_busqueda, nodo_actual, vecinos[i].nodo_2))
                {
                    vecinos.erase(vecinos.begin() + i);
                    i--;
                }
            for (unsigned int i = 0; i < vecinos.size(); i++)
            {
                devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, arbol_de_busqueda, 
                                                                    nodo_actual, informacion_del_hijo_a_adicionar);
                agrega_hijo_a_un_nodo(arbol_de_busqueda, nodo_actual, informacion_del_hijo_a_adicionar);
                Agenda.insert(Agenda.begin(), (unsigned int)(arbol_de_busqueda.size() - 1));
            }
        }
    }
    return false;
}

bool Busqueda::busqueda_profundidad_iterativa(string nodo_inicio, string nodo_final,
                                unsigned int limite_de_profundidad, unsigned int incremento_de_profundidad,
                                int& nodo_encontrado)
{
    unsigned int profundidad_actual = limite_de_profundidad; 
    do
    {
        if (busqueda_profundidad_limitada(nodo_inicio, nodo_final,
            profundidad_actual, nodo_encontrado))
            return true;
        profundidad_actual += incremento_de_profundidad;
    } while (true);
    return false;
}

bool Busqueda::existe_un_nodo_comun_en_las_agendas(vector<unsigned int> agenda_1, vector<unsigned int> agenda_2, 
                                                int& nodo_comun_inicio, int& nodo_comun_final) const
{
    for (auto elemento_agenda_1 = agenda_1.begin(); elemento_agenda_1 != agenda_1.end(); elemento_agenda_1++) 
        for (auto elemento_agenda_2 = agenda_2.begin(); elemento_agenda_2 != agenda_2.end(); elemento_agenda_2++)
            if (arbol_de_busqueda_desde_el_inicio[*elemento_agenda_1].contenido.nombre_del_nodo == 
                arbol_de_busqueda_desde_el_final[*elemento_agenda_2].contenido.nombre_del_nodo)
            {
                nodo_comun_inicio = *elemento_agenda_1;
                nodo_comun_final = *elemento_agenda_2;
                return true;
            }
    return false;
}

bool Busqueda::busqueda_bidireccional(string nodo_inicio, string nodo_final, int& nodo_encontrado_desde_el_inicio,
                                      int& nodo_encontrado_desde_el_final)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_nodo_final;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    int nodo_actual_desde_el_inicio = 0;
    int nodo_actual_desde_el_final = 0;
    vector<tipo_enlace_de_grafo> vecinos_desde_el_inicio;
    vector<tipo_enlace_de_grafo> vecinos_desde_el_final;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda_desde_el_inicio, 
                                                                -1, informacion_del_nodo_inicio))
        return false;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_final, arbol_de_busqueda_desde_el_final, 
                                                            -1, informacion_del_nodo_final))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda_desde_el_inicio);
    crea_arbol(informacion_del_nodo_final, arbol_de_busqueda_desde_el_final);
    Agenda_desde_el_inicio.clear();
    Agenda_desde_el_final.clear();
    Agenda_desde_el_inicio.push_back(0);
    Agenda_desde_el_final.push_back(0);
    while (true)
    {
        if (Agenda_desde_el_inicio.empty() && Agenda_desde_el_final.empty())
            return false;
        if (!Agenda_desde_el_inicio.empty())
        {
            nodo_actual_desde_el_inicio = Agenda_desde_el_inicio.front();
            Agenda_desde_el_inicio.erase(Agenda_desde_el_inicio.begin());
            if (arbol_de_busqueda_desde_el_inicio[nodo_actual_desde_el_inicio].contenido.nombre_del_nodo == nodo_final)
            {
                nodo_encontrado_desde_el_inicio = nodo_actual_desde_el_inicio;
                nodo_encontrado_desde_el_final = -1;
                return true;
            }
            devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda_desde_el_inicio[nodo_actual_desde_el_inicio].contenido.nombre_del_nodo,
                vecinos_desde_el_inicio);
            for (unsigned int i = 0; i < vecinos_desde_el_inicio.size(); i++)
                if (esta_un_nodo_en_ancestros(arbol_de_busqueda_desde_el_inicio,
                                              nodo_actual_desde_el_inicio,
                                              vecinos_desde_el_inicio[i].nodo_2))
                {
                    vecinos_desde_el_inicio.erase(vecinos_desde_el_inicio.begin() + i);
                    i--;
                }
            for (unsigned int i = 0; i < vecinos_desde_el_inicio.size(); i++)
            {
                devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos_desde_el_inicio[i].nodo_2,
                                                                    arbol_de_busqueda_desde_el_inicio,
                                                                    nodo_actual_desde_el_inicio,
                                                                    informacion_del_hijo_a_adicionar);
                agrega_hijo_a_un_nodo(arbol_de_busqueda_desde_el_inicio, 
                                        nodo_actual_desde_el_inicio, 
                                        informacion_del_hijo_a_adicionar);
                Agenda_desde_el_inicio.push_back((unsigned int)(arbol_de_busqueda_desde_el_inicio.size() - 1));
            }
        }
        if (!Agenda_desde_el_final.empty())
        {
            nodo_actual_desde_el_final = Agenda_desde_el_final.front();
            Agenda_desde_el_final.erase(Agenda_desde_el_final.begin());
            if (arbol_de_busqueda_desde_el_final[nodo_actual_desde_el_final].contenido.nombre_del_nodo == nodo_inicio)
            {
                nodo_encontrado_desde_el_inicio = -1;
                nodo_encontrado_desde_el_final = nodo_actual_desde_el_final;
                return true;
            }
            devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda_desde_el_final[nodo_actual_desde_el_final].contenido.nombre_del_nodo,
                                                vecinos_desde_el_final);
            for (unsigned int i = 0; i < vecinos_desde_el_final.size(); i++)
                if (esta_un_nodo_en_ancestros(arbol_de_busqueda_desde_el_final,
                                            nodo_actual_desde_el_final,
                                            vecinos_desde_el_final[i].nodo_2))
                {
                    vecinos_desde_el_final.erase(vecinos_desde_el_final.begin() + i);
                    i--;
                }
            for (unsigned int i = 0; i < vecinos_desde_el_final.size(); i++)
            {
                devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos_desde_el_final[i].nodo_2,
                                                                    arbol_de_busqueda_desde_el_final,
                                                                    nodo_actual_desde_el_final,
                                                                    informacion_del_hijo_a_adicionar);
                agrega_hijo_a_un_nodo(arbol_de_busqueda_desde_el_final,
                                      nodo_actual_desde_el_final,
                                    informacion_del_hijo_a_adicionar);
                Agenda_desde_el_final.push_back((unsigned int)(arbol_de_busqueda_desde_el_final.size() - 1));
            }
        }
        if (existe_un_nodo_comun_en_las_agendas(Agenda_desde_el_inicio, Agenda_desde_el_final,
            nodo_encontrado_desde_el_inicio, nodo_encontrado_desde_el_final))
            return true;
    }
    return false;
}

string Busqueda::devuelve_la_ruta_encontrada(int nodo_encontrado) const
{
    vector<unsigned int> temporal;
    string camino = "";
    temporal.clear();
    while (nodo_encontrado != -1)
    {
        temporal.push_back(nodo_encontrado);
        nodo_encontrado = arbol_de_busqueda[nodo_encontrado].padre;
    }
    for (int i = (int)(temporal.size() - 1); i >= 0; i--)
        camino = camino + " - " + arbol_de_busqueda[temporal[i]].contenido.nombre_del_nodo;
    camino.erase(camino.begin(), camino.begin() + 3);
    return camino;
}

string Busqueda::devuelve_la_ruta_encontrada_busqueda_bidireccional(int nodo_encontrado_desde_el_inicio,
                                                    int nodo_encontrado_desde_el_final) const
{
    vector<unsigned int> temporal;
    string camino_desde_el_inicio = "";
    string camino_desde_el_final = "";
    if (nodo_encontrado_desde_el_inicio != -1)
    {
        temporal.clear();
        while (nodo_encontrado_desde_el_inicio != -1)
        {
            temporal.push_back(nodo_encontrado_desde_el_inicio);
            nodo_encontrado_desde_el_inicio = arbol_de_busqueda_desde_el_inicio[nodo_encontrado_desde_el_inicio].padre;
        }
        for (int i = (int)(temporal.size() - 1); i >= 0; i--)
            camino_desde_el_inicio = camino_desde_el_inicio + " - " + 
                                     arbol_de_busqueda_desde_el_inicio[temporal[i]].contenido.nombre_del_nodo;
    }
    camino_desde_el_inicio.erase(camino_desde_el_inicio.begin(), camino_desde_el_inicio.begin() + 3);
    if (nodo_encontrado_desde_el_final != -1)
    {
        temporal.clear();
        nodo_encontrado_desde_el_final = arbol_de_busqueda_desde_el_final[nodo_encontrado_desde_el_final].padre;
        while (nodo_encontrado_desde_el_final != -1)
        {
            temporal.push_back(nodo_encontrado_desde_el_final);
            nodo_encontrado_desde_el_final = arbol_de_busqueda_desde_el_final[nodo_encontrado_desde_el_final].padre;
        }
        for (int i = (int)(temporal.size() - 1); i >= 0; i--)
            camino_desde_el_final = arbol_de_busqueda_desde_el_final[temporal[i]].contenido.nombre_del_nodo + " - " + camino_desde_el_final;
        camino_desde_el_final.erase(camino_desde_el_final.end() - 3, camino_desde_el_final.end());
    }
    return camino_desde_el_inicio + " - " + camino_desde_el_final;
}

bool Busqueda::busqueda_ascenso_a_la_colina(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int nodo_actual = 0;
    unsigned int mejor_nodo = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    Agenda.clear();
    Agenda.push_back(0);
    while (!Agenda.empty())
    {
        nodo_actual = Agenda.front();
        Agenda.erase(Agenda.begin());
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, arbol_de_busqueda,
                nodo_actual, informacion_del_hijo_a_adicionar);
            agrega_hijo_a_un_nodo(arbol_de_busqueda, nodo_actual, informacion_del_hijo_a_adicionar);
            Agenda.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
        }
        if (Agenda.size() == 0)
            return false;
        mejor_nodo = Agenda[0];
        for (unsigned int i = 1; i < Agenda.size(); i++)
            if (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado <
                arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado)
                mejor_nodo = Agenda[i];
        Agenda.clear();
        Agenda.push_back(mejor_nodo);
    }
    return false;
}

bool Busqueda::busqueda_primero_el_mejor(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int nodo_actual = 0;
    unsigned int temporal = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    Agenda.clear();
    Agenda.push_back(0);
    while (!Agenda.empty())
    {
        nodo_actual = Agenda.front();
        Agenda.erase(Agenda.begin());
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, arbol_de_busqueda,
                nodo_actual, informacion_del_hijo_a_adicionar);
            agrega_hijo_a_un_nodo(arbol_de_busqueda, nodo_actual, informacion_del_hijo_a_adicionar);
            Agenda.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
        }
        if (!Agenda.empty())
            for (unsigned int i = 0; i < Agenda.size() - 1; i++)
                for (unsigned int j = i + 1; j < Agenda.size(); j++)
                    if (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado > 
                        arbol_de_busqueda[Agenda[j]].contenido.costo_acumulado)
                    {
                        temporal = Agenda[i];
                        Agenda[i] = Agenda[j];
                        Agenda[j] = temporal;
                    }
    }
    return false;
}

bool Busqueda::busqueda_k_beans(string nodo_inicio, string nodo_final, unsigned int k, int& nodo_encontrado)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int nodo_actual = 0;
    unsigned int temporal = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    Agenda.clear();
    Agenda.push_back(0);
    while (!Agenda.empty())
    {
        nodo_actual = Agenda.front();
        Agenda.erase(Agenda.begin());
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, arbol_de_busqueda,
                nodo_actual, informacion_del_hijo_a_adicionar);
            agrega_hijo_a_un_nodo(arbol_de_busqueda, nodo_actual, informacion_del_hijo_a_adicionar);
            Agenda.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
        }
        if (!Agenda.empty())
            for (unsigned int i = 0; i < Agenda.size() - 1; i++)
                for (unsigned int j = i + 1; j < Agenda.size(); j++)
                    if (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado > arbol_de_busqueda[Agenda[j]].contenido.costo_acumulado)
                    {
                        temporal = Agenda[i];
                        Agenda[i] = Agenda[j];
                        Agenda[j] = temporal;
                    }
        if (Agenda.size() > k)
            Agenda.erase(Agenda.begin() + k, Agenda.end());
    }
    return false;
}

bool Busqueda::busqueda_branch_and_bound(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int mejor_nodo = 0;
    unsigned int posicion_del_mejor_nodo = 0;
    float costo_del_mejor_nodo = 0.0f;
    int meta_temporal = -1;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    Agenda.clear();
    Agenda.push_back(0);
    while (!Agenda.empty())
    {
        mejor_nodo = Agenda[0];
        posicion_del_mejor_nodo = 0;
        costo_del_mejor_nodo = arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado;
        for (unsigned int i = 1; i < Agenda.size(); i++)
            if (costo_del_mejor_nodo >
                (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado))
            {
                mejor_nodo = Agenda[i];
                posicion_del_mejor_nodo = i;
                costo_del_mejor_nodo = arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado;
            }
        Agenda.erase(Agenda.begin() + posicion_del_mejor_nodo);
        if (arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo == nodo_final)
        {
            if (meta_temporal == -1)
                meta_temporal = mejor_nodo;
            else
                if (arbol_de_busqueda[meta_temporal].contenido.costo_acumulado > 
                    arbol_de_busqueda[Agenda[mejor_nodo]].contenido.costo_acumulado)
                    meta_temporal = mejor_nodo;
            for (unsigned int i = 0; i < Agenda.size(); i++)
                if (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado >= 
                    arbol_de_busqueda[meta_temporal].contenido.costo_acumulado)
                {
                    Agenda.erase(Agenda.begin() + i);
                    i--;
                }
            if (Agenda.empty())
            {
                nodo_encontrado = meta_temporal;
                return true;
            }
        }
        devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, mejor_nodo, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, arbol_de_busqueda,
                mejor_nodo, informacion_del_hijo_a_adicionar);
            if (meta_temporal != -1)
                if (arbol_de_busqueda[meta_temporal].contenido.costo_acumulado <
                    informacion_del_hijo_a_adicionar.costo_acumulado)
                    continue;
            agrega_hijo_a_un_nodo(arbol_de_busqueda, mejor_nodo, informacion_del_hijo_a_adicionar);
            Agenda.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
        }
    }
    nodo_encontrado = meta_temporal;
    return meta_temporal != -1;
}

float Busqueda::calcula_heuristica_a_la_meta(string nodo_actual, string meta) const
{
    float calculo = 0.0f;
    float x1 = 0.0f;
    float y1 = 0.0f;
    float x2 = 0.0f;
    float y2 = 0.0f;
    for (size_t i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo_1 == nodo_actual)
        {
            x1 = grafo[i].posicion_x_nodo_1;
            y1 = grafo[i].posicion_y_nodo_1;
            break;
        }
        else if (grafo[i].nodo_2 == nodo_actual)
        {
            x1 = grafo[i].posicion_x_nodo_2;
            y1 = grafo[i].posicion_y_nodo_2;
            break;
        }
    for (size_t i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo_1 == meta)
        {
            x2 = grafo[i].posicion_x_nodo_1;
            y2 = grafo[i].posicion_y_nodo_1;
            break;
        }
        else if (grafo[i].nodo_2 == meta)
        {
            x2 = grafo[i].posicion_x_nodo_2;
            y2 = grafo[i].posicion_y_nodo_2;
            break;
        }
    calculo = (float)pow(pow(x2 - x1, 2) + pow(y2 - y1, 2), 0.5);
    return calculo;
}

bool Busqueda::busqueda_A_estrella(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int mejor_nodo = 0;
    unsigned int posicion_del_mejor_nodo = 0;
    float costo_del_mejor_nodo = 0.0f;
    int meta_temporal = -1;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    arbol_de_busqueda[0].contenido.costo_estimado = calcula_heuristica_a_la_meta(nodo_inicio, nodo_final);
    Agenda.clear();
    Agenda.push_back(0);
    while (!Agenda.empty())
    {
        mejor_nodo = Agenda[0];
        posicion_del_mejor_nodo = 0;
        costo_del_mejor_nodo = arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado +
                               arbol_de_busqueda[mejor_nodo].contenido.costo_estimado;
        for (unsigned int i = 1; i < Agenda.size(); i++)
            if (costo_del_mejor_nodo >
                (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado +
                    arbol_de_busqueda[Agenda[i]].contenido.costo_estimado))
            {
                mejor_nodo = Agenda[i];
                posicion_del_mejor_nodo = i;
                costo_del_mejor_nodo = arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado +
                                       arbol_de_busqueda[mejor_nodo].contenido.costo_estimado;
            }
        Agenda.erase(Agenda.begin() + posicion_del_mejor_nodo);
        if (arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo == nodo_final)
        {
            if (meta_temporal == -1)
                meta_temporal = mejor_nodo;
            else if (arbol_de_busqueda[meta_temporal].contenido.costo_acumulado >
                arbol_de_busqueda[Agenda[mejor_nodo]].contenido.costo_acumulado)
                meta_temporal = mejor_nodo;
            for (unsigned int i = 0; i < Agenda.size(); i++)
                if (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado >=
                    arbol_de_busqueda[meta_temporal].contenido.costo_acumulado)
                {
                    Agenda.erase(Agenda.begin() + i);
                    i--;
                }
            if (Agenda.empty())
            {
                nodo_encontrado = meta_temporal;
                return true;
            }
        }
        devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, mejor_nodo, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, arbol_de_busqueda,
                mejor_nodo, informacion_del_hijo_a_adicionar);
            if (meta_temporal != -1)
                if (arbol_de_busqueda[meta_temporal].contenido.costo_acumulado <
                    informacion_del_hijo_a_adicionar.costo_acumulado)
                    continue;
            informacion_del_hijo_a_adicionar.costo_estimado = calcula_heuristica_a_la_meta(vecinos[i].nodo_2,
                                                                    nodo_final);
            agrega_hijo_a_un_nodo(arbol_de_busqueda, mejor_nodo, informacion_del_hijo_a_adicionar);
            Agenda.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
        }
    }
    nodo_encontrado = meta_temporal;
    return meta_temporal != -1;
}



