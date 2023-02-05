#include <iostream>
#include "Grafo.h"

using namespace std;
int main()
{
  Grafo grafo;
  grafo.leerGrafo("Ciudades de Mexico.csv");
  for(auto enlace : grafo.enlaces)
  {
    cout << enlace.nodo1 << " " << enlace.costo1 << " " << enlace.posicionx_1 << " " << enlace.posiciony_1 << " " << enlace.nodo2 << " " << enlace.costo2 << " " << enlace.posicionx_2 << " " << enlace.posiciony_2 << " " << enlace.costo_enlace << endl;
  }
  return 0;
}
