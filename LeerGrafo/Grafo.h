#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct tipo_enlace_de_grafo
{
    string nodo1 = "";
    float costo1 = 0;
    float posicionx_1 = 0;
    float posiciony_1 = 0;
    string nodo2 = "";
    float costo2 = 0;
    float posicionx_2 = 0;
    float posiciony_2 = 0;
    float costo_enlace = 0;
    tipo_enlace_de_grafo(string nodo1, float costo1, float posicionx_1, float posiciony_1, string nodo2, float costo2, float posicionx_2, float posiciony_2, float costo_enlace)
    {
        this->nodo1 = nodo1;
        this->costo1 = costo1;
        this->posicionx_1 = posicionx_1;
        this->posiciony_1 = posiciony_1;
        this->nodo2 = nodo2;
        this->costo2 = costo2;
        this->posicionx_2 = posicionx_2;
        this->posiciony_2 = posiciony_2;
        this->costo_enlace = costo_enlace;
    }
};

class Grafo
{
    public:
        vector<tipo_enlace_de_grafo> enlaces;
        void leerGrafo(string nombre_archivo);
};
