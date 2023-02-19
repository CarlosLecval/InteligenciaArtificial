#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

struct Enlace
{
    string nombre;
    float costo_enlace;
    Enlace* next;
    Enlace(string, float);
};

struct Nodo
{
    float costo_ciudad = 0;
    float coordenada_x = 0;
    float coordenada_y = 0;
    Enlace* head = nullptr;
};

class Grafo
{
    public:
        Grafo();
        void lee_grafo(string);
        void imprimir_grafo();
    private:
        unordered_map<string, Nodo> grafo;
};
