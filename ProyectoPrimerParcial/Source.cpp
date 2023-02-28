#include <iostream>
#include "Grafo.h"
#include "Busqueda.h"

using namespace std;
int main()
{
  Grafo g("Grafo.csv");
  Busqueda b(g);
  int nodo_encontrado = -1;
  int nodo_encontrado_final = -1;
  //b.busqueda_bidireccional("A", "F", nodo_encontrado, nodo_encontrado_final);
  b.busqueda_primero_en_profundidad("A", "F", nodo_encontrado);
  if(nodo_encontrado == -1 && nodo_encontrado_final == -1) cout << "No se encontro el nodo" << endl;
  else cout << b.devuelve_la_ruta_encontrada(nodo_encontrado) << endl;
  /*b.busqueda_a_lo_ancho("A", "F", nodo_encontrado);
  if(nodo_encontrado != -1) cout << b.devuelve_la_ruta_encontrada(nodo_encontrado) << endl;
  else cout << "No se encontro el nodo" << endl;*/
  return 0;
}
