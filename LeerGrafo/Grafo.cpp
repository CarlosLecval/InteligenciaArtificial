#include "Grafo.h"

void Grafo::leerGrafo(string nombre_archivo)
{
    string line;
    ifstream myfile(nombre_archivo);
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
        tipo_enlace_de_grafo enlace(nodo1, costo1, posicionx_1, posiciony_1, nodo2, costo2, posicionx_2, posiciony_2, costo_enlace);
        enlaces.push_back(enlace);
    }
    myfile.close();
}