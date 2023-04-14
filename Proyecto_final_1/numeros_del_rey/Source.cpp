#include <iostream>
#include "Grafo.h"
#include "Busqueda.h"

using namespace std;
int main()
{
  Grafo g;
  int nodo_encontrado = -1;
  int numero_a_buscar = 0;
  string opc = "s";
  while (opc != "n") {
    Busqueda b(g);
    cout << "Ingrese el numero a buscar: ";
    cin >> numero_a_buscar;
    b.busqueda_primero_en_profundidad_numeros_del_rey(numero_a_buscar, nodo_encontrado);
    if (nodo_encontrado == -1) {
      cout << "No se encontro el nodo" << endl;
    }
    else 
    {
      cout << b.devuelve_la_ruta_encontrada_numeros_del_rey(nodo_encontrado) << endl;
    }
    cout << "Desea buscar otro numero? (s/n): ";
    cin >> opc;
    nodo_encontrado = -1;
  }
}
