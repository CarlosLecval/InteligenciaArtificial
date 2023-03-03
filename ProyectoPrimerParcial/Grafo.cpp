#include "Grafo.h"


Grafo::Grafo()
{
}

Grafo::Grafo(string archivo)
{
    string line;
    ifstream myfile(archivo);
    getline(myfile, line);
    while(getline(myfile, line))
    {
        stringstream ss(line);
        string nodo1, nodo2;
        float costo1, costo2, posicionx_1, posiciony_1, posicionx_2, posiciony_2, costo_enlace;
        getline(ss, nodo1, ',');
        ss >> costo1;
        ss.ignore();
        ss >> posicionx_1;
        ss.ignore();
        ss >> posiciony_1;
        ss.ignore();
        getline(ss, nodo2, ',');
        ss >> costo2;
        ss.ignore();
        ss >> posicionx_2;
        ss.ignore();
        ss >> posiciony_2;
        ss.ignore();
        ss >> costo_enlace;
        if(grafo.find(nodo1) == grafo.end())
        {
            grafo[nodo1].costo_ciudad = costo1;
            grafo[nodo1].coordenada_x = posicionx_1;
            grafo[nodo1].coordenada_y = posiciony_1;
        }
        grafo[nodo1].vecinos[nodo2] = costo_enlace;
        if(grafo.find(nodo2) == grafo.end())
        {
            grafo[nodo2].costo_ciudad = costo2;
            grafo[nodo2].coordenada_x = posicionx_2;
            grafo[nodo2].coordenada_y = posiciony_2;
        }
        grafo[nodo2].vecinos[nodo1] = costo_enlace;
    }
    myfile.close();
}

bool Grafo::devuelve_informacion_de_un_nodo(string nodo, Nodo& nodo_devuelto) const
{
    if(grafo.find(nodo) != grafo.end())
    {
        nodo_devuelto = grafo.at(nodo);
        return true;
    }
    return false;
}

unordered_map<string, float> Grafo::devuelve_vecinos_de_un_nodo(string nodo) const
{
    return grafo.at(nodo).vecinos;
}