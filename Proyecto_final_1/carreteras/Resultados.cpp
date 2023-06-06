#include "Resultados.h"

void Resultados::printRutas(string nodo_inicio, string nodo_final, Busqueda &b_grafo, bool dirigido, int limite_profunidad, int &costo)
{
    int nodo_encontrado = -1, nodo_encontrado_final = -1;
    stringstream tabla;
    cout << endl
         << "Rutas de " << nodo_inicio << " a " << nodo_final << endl
         << endl;
    if (!dirigido)
    {
        tabla << "Tabla para grafo no dirigido de " << nodo_inicio << " a " << nodo_final << endl;
    }
    else
    {
        tabla << "Tabla para grafo dirigido de " << nodo_inicio << " a " << nodo_final << endl;
    }
    tabla << setw(42) << left << "Algoritmo" << setw(3) << " | " << setw(10) << left << "Agenda" << setw(10) << left << "Arbol" << endl;
    string temp = "";
    for (int i = 0; i < 65; i++)
    {
        temp += "-";
    }
    tabla << temp << endl;
    cout << "Busqueda primero a lo ancho" << endl;
    tabla << setw(42) << left << "Busqueda primero a lo ancho" << setw(3) << left << " | ";
    if (b_grafo.busqueda_a_lo_ancho(nodo_inicio, nodo_final, nodo_encontrado))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl
             << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    tabla << temp << endl;
    cout << "Busqueda primero en profundidad" << endl;
    tabla << setw(42) << left << "Busqueda primero en profundidad" << setw(3) << left << " | ";
    if (b_grafo.busqueda_primero_en_profundidad(nodo_inicio, nodo_final, nodo_encontrado))
    {
      cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl << endl;
      tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else {
      cout << "no se encontró la ruta" << endl << endl;
      tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    tabla << temp << endl;
    cout << "Busqueda primero en profundidad limitada" << endl;
    tabla << setw(42) << left << "Busqueda primero en profundidad limitada" << setw(3) << left << " | ";
    if (b_grafo.busqueda_primero_en_profundidad_limitada(nodo_inicio, nodo_final, nodo_encontrado, limite_profunidad))
    {
      cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl << endl;
      tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else {
      cout << "no se encontró la ruta" << endl << endl;
      tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    tabla << temp << endl;
    cout << "Busqueda primero en profundidad iterativa" << endl;
    tabla << setw(42) << left << "Busqueda primero en profundidad iterativa" << setw(3) << left << " | ";
    if (b_grafo.busqueda_primero_en_profundidad_iterativa(nodo_inicio, nodo_final, nodo_encontrado, 3, 2))
    {
      cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl << endl;
      tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else {
      cout << "no se encontró la ruta" << endl << endl;
      tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda bidireccional" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda bidireccional" << setw(3) << left << " | ";
    if (b_grafo.busqueda_bidireccional(nodo_inicio, nodo_final, nodo_encontrado, nodo_encontrado_final))
    {
        if (nodo_encontrado_final == -1)
        {
            cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl
                 << endl;
        }
        else if (nodo_encontrado == -1)
        {
            cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado_final, costo) << endl
                 << endl;
        }
        else
        {
            cout << b_grafo.devuelve_la_ruta_bidireccional(nodo_encontrado, nodo_encontrado_final) << endl
                 << endl;
        }
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda ascenso a la colina" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda ascenso a la colina" << setw(3) << left << " | ";
    if (b_grafo.busqueda_ascenso_a_la_colina(nodo_inicio, nodo_final, nodo_encontrado))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl;
        cout << "Costo: " << costo << endl << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda primero el mejor" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda primero el mejor" << setw(3) << left << " | ";
    if (b_grafo.busqueda_primero_el_mejor(nodo_inicio, nodo_final, nodo_encontrado))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl;
        cout << "Costo: " << costo << endl << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda k beams" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda k beams" << setw(3) << left << " | ";
    if (b_grafo.beam_search(nodo_inicio, nodo_final, nodo_encontrado, 10))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl;
        cout << "Costo: " << costo << endl << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda branch and bound" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda branch and bound" << setw(3) << left << " | ";
    if (b_grafo.branch_and_bound(nodo_inicio, nodo_final, nodo_encontrado))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl;
        cout << "Costo: " << costo << endl << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda a estrella" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda a estrella" << setw(3) << left << " | ";
    if (b_grafo.busqueda_a_estrella(nodo_inicio, nodo_final, nodo_encontrado))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl;
        cout << "Costo: " << costo << endl << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    cout << endl
         << tabla.str() << endl;
}

void Resultados::printRutasSinProfunidad(string nodo_inicio, string nodo_final, Busqueda &b_grafo, bool dirigido, int &costo)
{
    int nodo_encontrado = -1, nodo_encontrado_final = -1;
    stringstream tabla;
    cout << endl
         << "Rutas de " << nodo_inicio << " a " << nodo_final << endl
         << endl;
    if (!dirigido)
    {
        tabla << "Tabla para grafo no dirigido de " << nodo_inicio << " a " << nodo_final << endl;
    }
    else
    {
        tabla << "Tabla para grafo dirigido de " << nodo_inicio << " a " << nodo_final << endl;
    }
    tabla << setw(42) << left << "Algoritmo" << setw(3) << " | " << setw(10) << left << "Agenda" << setw(10) << left << "Arbol" << endl;
    string temp = "";
    for (int i = 0; i < 65; i++)
    {
        temp += "-";
    }
    tabla << temp << endl;
    cout << "Busqueda primero a lo ancho" << endl;
    tabla << setw(42) << left << "Busqueda primero a lo ancho" << setw(3) << left << " | ";
    if (b_grafo.busqueda_a_lo_ancho(nodo_inicio, nodo_final, nodo_encontrado))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl
             << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda primero en profundidad" << setw(3) << left << " | ";
    tabla << setw(20) << left << "Excede RAM" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda primero en profundidad limitada" << setw(3) << left << " | ";
    tabla << setw(20) << left << "Excede RAM" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda primero en profundidad iterativa" << setw(3) << left << " | ";
    tabla << setw(20) << left << "Excede RAM" << endl;
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda bidireccional" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda bidireccional" << setw(3) << left << " | ";
    if (b_grafo.busqueda_bidireccional(nodo_inicio, nodo_final, nodo_encontrado, nodo_encontrado_final))
    {
        if (nodo_encontrado_final == -1)
        {
            cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl
                 << endl;
        }
        else if (nodo_encontrado == -1)
        {
            cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado_final, costo) << endl
                 << endl;
        }
        else
        {
            cout << b_grafo.devuelve_la_ruta_bidireccional(nodo_encontrado, nodo_encontrado_final) << endl
                 << endl;
        }
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda ascenso a la colina" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda ascenso a la colina" << setw(3) << left << " | ";
    if (b_grafo.busqueda_ascenso_a_la_colina(nodo_inicio, nodo_final, nodo_encontrado))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl;
        cout << "Costo: " << costo << endl << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda primero el mejor" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda primero el mejor" << setw(3) << left << " | ";
    if (b_grafo.busqueda_primero_el_mejor(nodo_inicio, nodo_final, nodo_encontrado))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl;
        cout << "Costo: " << costo << endl << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda k beams" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda k beams" << setw(3) << left << " | ";
    if (b_grafo.beam_search(nodo_inicio, nodo_final, nodo_encontrado, 5))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl;
        cout << "Costo: " << costo << endl << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda branch and bound" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda branch and bound" << setw(3) << left << " | ";
    if (b_grafo.branch_and_bound(nodo_inicio, nodo_final, nodo_encontrado))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl;
        cout << "Costo: " << costo << endl << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda a estrella" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda a estrella" << setw(3) << left << " | ";
    if (b_grafo.busqueda_a_estrella(nodo_inicio, nodo_final, nodo_encontrado))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl;
        cout << "Costo: " << costo << endl << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    cout << endl
         << tabla.str() << endl;
}

void Resultados::printRutasAberdeen(string nodo_inicio, string nodo_final, Busqueda &b_grafo, bool dirigido, int limite_profunidad, int &costo)
{
    int nodo_encontrado = -1, nodo_encontrado_final = -1;
    stringstream tabla;
    cout << endl
         << "Rutas de " << nodo_inicio << " a " << nodo_final << endl
         << endl;
    if (!dirigido)
    {
        tabla << "Tabla para grafo no dirigido de " << nodo_inicio << " a " << nodo_final << endl;
    }
    else
    {
        tabla << "Tabla para grafo dirigido de " << nodo_inicio << " a " << nodo_final << endl;
    }
    tabla << setw(42) << left << "Algoritmo" << setw(3) << " | " << setw(10) << left << "Agenda" << setw(10) << left << "Arbol" << endl;
    string temp = "";
    for (int i = 0; i < 65; i++)
    {
        temp += "-";
    }
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda primero a lo ancho" << setw(3) << left << " | ";
    tabla << setw(20) << left << "RAM excedida" << endl;
    nodo_encontrado = -1;
    b_grafo.reset_max();
    tabla << temp << endl;
    cout << "Busqueda primero en profundidad" << endl;
    tabla << setw(42) << left << "Busqueda primero en profundidad" << setw(3) << left << " | ";
    if (b_grafo.busqueda_primero_en_profundidad(nodo_inicio, nodo_final, nodo_encontrado))
    {
      cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl << endl;
      tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else {
      cout << "no se encontró la ruta" << endl << endl;
      tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    tabla << temp << endl;
    cout << "Busqueda primero en profundidad limitada" << endl;
    tabla << setw(42) << left << "Busqueda primero en profundidad limitada" << setw(3) << left << " | ";
    if (b_grafo.busqueda_primero_en_profundidad_limitada(nodo_inicio, nodo_final, nodo_encontrado, limite_profunidad))
    {
      cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl << endl;
      tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else {
      cout << "no se encontró la ruta" << endl << endl;
      tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    tabla << temp << endl;
    cout << "Busqueda primero en profundidad iterativa" << endl;
    tabla << setw(42) << left << "Busqueda primero en profundidad iterativa" << setw(3) << left << " | ";
    if (b_grafo.busqueda_primero_en_profundidad_iterativa(nodo_inicio, nodo_final, nodo_encontrado, 3, 2))
    {
      cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl << endl;
      tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else {
      cout << "no se encontró la ruta" << endl << endl;
      tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda bidireccional" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda bidireccional" << setw(3) << left << " | ";
    if (b_grafo.busqueda_bidireccional(nodo_inicio, nodo_final, nodo_encontrado, nodo_encontrado_final))
    {
        if (nodo_encontrado_final == -1)
        {
            cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl
                 << endl;
        }
        else if (nodo_encontrado == -1)
        {
            cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado_final, costo) << endl
                 << endl;
        }
        else
        {
            cout << b_grafo.devuelve_la_ruta_bidireccional(nodo_encontrado, nodo_encontrado_final) << endl
                 << endl;
        }
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda ascenso a la colina" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda ascenso a la colina" << setw(3) << left << " | ";
    if (b_grafo.busqueda_ascenso_a_la_colina(nodo_inicio, nodo_final, nodo_encontrado))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl;
        cout << "Costo: " << costo << endl << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda primero el mejor" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda primero el mejor" << setw(3) << left << " | ";
    if (b_grafo.busqueda_primero_el_mejor(nodo_inicio, nodo_final, nodo_encontrado))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl;
        cout << "Costo: " << costo << endl << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda k beams" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda k beams" << setw(3) << left << " | ";
    if (b_grafo.beam_search(nodo_inicio, nodo_final, nodo_encontrado, 5))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl;
        cout << "Costo: " << costo << endl << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda branch and bound" << setw(3) << left << " | ";
    tabla << setw(20) << left << "Tarda demasiado" << endl;
    nodo_encontrado = -1;
    b_grafo.reset_max();
    cout << "Busqueda a estrella" << endl;
    tabla << temp << endl;
    tabla << setw(42) << left << "Busqueda a estrella" << setw(3) << left << " | ";
    if (b_grafo.busqueda_a_estrella(nodo_inicio, nodo_final, nodo_encontrado))
    {
        cout << "Ruta encontrada: " << b_grafo.devuelve_la_ruta_encontrada(nodo_encontrado, costo) << endl;
        cout << "Costo: " << costo << endl << endl;
        tabla << setw(10) << left << b_grafo.devuelve_max_agenda() << setw(10) << left << b_grafo.devuelve_max_arbol() << endl;
    }
    else
    {
        cout << "no se encontró la ruta" << endl
             << endl;
        tabla << setw(20) << left << "no se encontró la ruta" << endl;
    }
    cout << endl
         << tabla.str() << endl;
}
