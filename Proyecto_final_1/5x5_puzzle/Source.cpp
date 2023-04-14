#include <iostream>
#include "Busqueda.h"

using namespace std;
int main()
{
  int nodo_encontrado, nodo_encontrado_final;
  int opcion;
  string nodo_inicio, nodo_final;
  Busqueda busqueda;
  cout<<"Ingrese el nodo de inicio: ";
  cin>>nodo_inicio;
  cout<<"Ingrese el nodo final: ";
  cin>>nodo_final;
  busqueda.best_first(nodo_inicio, nodo_final, nodo_encontrado);
  cout<<"La ruta encontrada es:"<<busqueda.devuelve_la_ruta_encontrada(nodo_encontrado)<<endl;
  return 0;
}
