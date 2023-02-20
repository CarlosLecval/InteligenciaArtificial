#include "Busqueda.h"
#include "malloc.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	Busqueda p;
	string camino;
	int nodoencontrado = -1;
	if (p.lee_grafo("Grafo.csv"))
	{
		/*if (p.busqueda_primero_en_profundidad("S", "G", nodoencontrado))
			camino = p.devuelve_la_ruta_encontrada(nodoencontrado);
			cout << camino << endl;*/
		p.busqueda_bidireccional("S", "G", nodoencontrado);
	}
	return 0;
}