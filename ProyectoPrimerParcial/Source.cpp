#include <iostream>
#include "Grafo.h"

using namespace std;
int main()
{
  Grafo g;
  g.lee_grafo("Grafo.csv");
  g.imprimir_grafo();

  return 0;
}
