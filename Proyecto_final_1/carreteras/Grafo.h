#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Nodo
{
    float costo_ciudad = 0;
    float coordenada_x = 0;
    float coordenada_y = 0;
    unordered_map<string, float> vecinos;
};

class Grafo
{
    public:
        Grafo();
        Grafo(string, bool);
        bool devuelve_informacion_de_un_nodo(string, Nodo&) const;
        unordered_map<string, float> devuelve_vecinos_de_un_nodo(string nodo) const;
    private:
        unordered_map<string, Nodo> grafo;
};
