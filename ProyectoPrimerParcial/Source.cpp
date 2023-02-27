#include <iostream>
#include "Grafo.h"
#include "Busqueda.h"

using namespace std;
int main()
{
  Grafo g("Grafo.csv");
  Busqueda b(g);
  int nodo_encontrado = -1;
  b.busqueda_a_lo_ancho("A", "F", nodo_encontrado);
  if(nodo_encontrado != -1) cout << b.devuelve_la_ruta_encontrada(nodo_encontrado) << endl;
  else cout << "No se encontro el nodo" << endl;
  return 0;
}
