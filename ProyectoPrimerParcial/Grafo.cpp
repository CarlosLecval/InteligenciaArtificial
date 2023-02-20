#include "Grafo.h"

Enlace::Enlace(string nombre, float costo_enlace)
{
    this->nombre = nombre;
    this->costo_enlace = costo_enlace;
    this->next = nullptr;
}

Grafo::Grafo()
{
    //this->grafo = unordered_map<string, Nodo>();
}

void Grafo::lee_grafo(string archivo)
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
            grafo[nodo1].head = new Enlace(nodo2, costo_enlace);
        }
        else{
            Enlace* temp = grafo[nodo1].head;
            grafo[nodo1].head = new Enlace(nodo2, costo_enlace);
            grafo[nodo1].head->next = temp;
        }
        if(grafo.find(nodo2) == grafo.end())
        {
            grafo[nodo2].costo_ciudad = costo2;
            grafo[nodo2].coordenada_x = posicionx_2;
            grafo[nodo2].coordenada_y = posiciony_2;
            grafo[nodo2].head = new Enlace(nodo1, costo_enlace);
        }
        else{
            Enlace* temp = grafo[nodo2].head;
            grafo[nodo2].head = new Enlace(nodo1, costo_enlace);
            grafo[nodo2].head->next = temp;
        }
    }
    myfile.close();
}

void Grafo::imprimir_grafo()
{
    for(auto it = grafo.begin(); it != grafo.end(); it++)
    {
        cout << it->first << " " << it->second.costo_ciudad << " " << it->second.coordenada_x << " " << it->second.coordenada_y << endl;
        Enlace* temp = it->second.head;
        while(temp != nullptr)
        {
            cout << temp->nombre << " " << temp->costo_enlace << endl;
            temp = temp->next;
        }
        cout << endl;
    }
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