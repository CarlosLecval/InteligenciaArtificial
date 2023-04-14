#include "Arbol.h"
Arbol::Arbol()
{
}

Arbol::Arbol(string nodo_final)
{
    this->nodo_final = nodo_final;
}


void Arbol::crea_arbol(Nodo_informacion contenido)
{
    arbol_de_busqueda.clear();
    Nodo_del_arbol temporal;
    temporal.contenido = contenido;
    temporal.hijos.clear();
    arbol_de_busqueda.push_back(temporal);
}

void Arbol::devuelve_informacion_de_un_vertice_grafo_no_dirigido(string nombre_nodo, int padre_nodo, Nodo_informacion& informacion_nodo)
{
    informacion_nodo.nombre = nombre_nodo;
    if(padre_nodo != -1)
    {
        informacion_nodo.profundidad = arbol_de_busqueda[padre_nodo].contenido.profundidad + 1;
    }
    else
    {
        informacion_nodo.profundidad = 0;
    }
}

int Arbol::devuelve_profundidad_del_nodo(int posicion_nodo)
{
    return arbol_de_busqueda[posicion_nodo].contenido.profundidad;
}

float Arbol::devuelve_costo_acumulado_del_nodo(int posicion_nodo) const
{
    return arbol_de_busqueda[posicion_nodo].contenido.costo_acumulado;
}

void Arbol::agrega_hijo_a_un_nodo(int padre, Nodo_informacion contenido)
{
    Nodo_del_arbol temporal;
    temporal.contenido = contenido;
    temporal.padre = padre;
    temporal.hijos.clear();
    arbol_de_busqueda.push_back(temporal);
    arbol_de_busqueda[padre].hijos.push_back((unsigned int)arbol_de_busqueda.size() - 1);
}

bool Arbol::esta_un_nodo_en_ancestros(int nodo_origen, string nodo_presunto_ancestro) const
{
    while(nodo_origen != -1)
    {
        if(arbol_de_busqueda[nodo_origen].contenido.nombre == nodo_presunto_ancestro)
            return true;
        nodo_origen = arbol_de_busqueda[nodo_origen].padre;
    }
    return false;
}

int Arbol::devuelve_tamano_del_arbol() const
{
    return (int)arbol_de_busqueda.size();
}

string Arbol::devuelve_nombre_de_un_nodo(int nodo) const
{
    return arbol_de_busqueda[nodo].contenido.nombre;
}

int Arbol::devuelve_padre_de_un_nodo(int nodo) const
{
    return arbol_de_busqueda[nodo].padre;
}

int Arbol::devuelve_heuristica(int nodo)
{
    //suma de las distancias de manhattan de cada ficha a su posicion final
    int heuristica = 0;
    for(int i = 0; i < 25; i++)
    {
        if(arbol_de_busqueda[nodo].contenido.nombre[i] != '0')
        {
            int fila = (nodo_final.find(arbol_de_busqueda[nodo].contenido.nombre[i]) / 5) - i / 5;
            int columna = nodo_final.find(arbol_de_busqueda[nodo].contenido.nombre[i]) % 5 - i % 5;
            heuristica += abs(fila) + abs(columna);
        }
    }
    return heuristica;
}

void encontrar_vacios(string puzzle, int& row_1, int& col_1, int& row_2, int& col_2)
{
    bool primero = true;
    for(int i = 0; i < 25; i++)
    {
        if(puzzle[i] == '0' && primero)
        {
            row_2 = i / 5;
            col_2 = i % 5;
            primero = false;
        }
        else if(puzzle[i] == '0' && !primero)
        {
            row_1 = i / 5;
            col_1 = i % 5;
            return;
        }
    }
}

void swap(string& puzzle, int i, int j)
{
    char temp = puzzle[i];
    puzzle[i] = puzzle[j];
    puzzle[j] = temp;
}

vector<string> Arbol::devuelve_vecinos_de_un_nodo(string puzzle)
{
    vector<string> neighbors;
    int row_1, col_1, row_2, col_2;
    encontrar_vacios(puzzle, row_1, col_1, row_2, col_2);

    // Si el espacio vacío no está en la primera fila, podemos mover la pieza superior
    if (row_1 > 0) {
        string neighbor = puzzle;
        swap(neighbor, 5 * (row_1 - 1) + col_1, 5 * row_1 + col_1);
        if(puzzle[5 * (row_1 - 1) + col_1] != puzzle[5 * row_1 + col_1])
            neighbors.push_back(neighbor);
    }

    // Si el espacio vacío no está en la última fila, podemos mover la pieza inferior
    if (row_1 < 4) {
        string neighbor = puzzle;
        swap(neighbor, 5 * (row_1 + 1) + col_1, 5 * row_1 + col_1);
        if(puzzle[5 * (row_1 + 1) + col_1] != puzzle[5 * row_1 + col_1])
            neighbors.push_back(neighbor);
    }

    // Si el espacio vacío no está en la primera columna, podemos mover la pieza izquierda
    if (col_1 > 0) {
        string neighbor = puzzle;
        swap(neighbor, 5 * row_1 + col_1 - 1, 5 * row_1 + col_1);
        if(puzzle[5 * row_1 + col_1 - 1] != puzzle[5 * row_1 + col_1])
            neighbors.push_back(neighbor);
    }

    // Si el espacio vacío no está en la última columna, podemos mover la pieza derecha
    if (col_1 < 4) {
        string neighbor = puzzle;
        swap(neighbor, 5 * row_1 + col_1 + 1, 5 * row_1 + col_1);
        if(puzzle[5 * row_1 + col_1 + 1] != puzzle[5 * row_1 + col_1])
            neighbors.push_back(neighbor);
    }

    if (row_2 > 0) {
        string neighbor = puzzle;
        swap(neighbor, 5 * (row_2 - 1) + col_2, 5 * row_2 + col_2);
        if(puzzle[5 * (row_2 - 1) + col_2] != puzzle[5 * row_2 + col_2])
            neighbors.push_back(neighbor);
    }

    // Si el espacio vacío no está en la última fila, podemos mover la pieza inferior
    if (row_2 < 4) {
        string neighbor = puzzle;
        swap(neighbor, 5 * (row_2 + 1) + col_2, 5 * row_2 + col_2);
        if(puzzle[5 * (row_2 + 1) + col_2] != puzzle[5 * row_2 + col_2])
            neighbors.push_back(neighbor);
    }

    // Si el espacio vacío no está en la primera columna, podemos mover la pieza izquierda
    if (col_2 > 0) {
        string neighbor = puzzle;
        swap(neighbor, 5 * row_2 + col_2 - 1, 5 * row_2 + col_2);
        if(puzzle[5 * row_2 + col_2 - 1] != puzzle[5 * row_2 + col_2])
            neighbors.push_back(neighbor);
    }

    // Si el espacio vacío no está en la última columna, podemos mover la pieza derecha
    if (col_2 < 4) {
        string neighbor = puzzle;
        swap(neighbor, 5 * row_2 + col_2 + 1, 5 * row_2 + col_2);
        if(puzzle[5 * row_2 + col_2 + 1] != puzzle[5 * row_2 + col_2])
            neighbors.push_back(neighbor);
    }

    //Ver vecinos
    /*cout << "Vecinos de " << puzzle << endl;
    for(int i = 0; i < neighbors.size(); i++)
    {
        cout << neighbors[i] << endl;
    }*/

    return neighbors;
}
