#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Enlace
{
    string nombre;
    float costo_enlace;
    Enlace(string, float);
};

struct Nodo
{
    float costo_ciudad = 0;
    float coordenada_x = 0;
    float coordenada_y = 0;
    vector<Enlace> vecinos;
};

class Grafo
{
    public:
        Grafo();
        void lee_grafo(string);
        void imprimir_grafo();
        bool devuelve_informacion_de_un_nodo(string, Nodo&) const;
        void devuelve_vecinos_de_un_nodo(string, vector<string>&) const;
    private:
        unordered_map<string, Nodo> grafo;
};
