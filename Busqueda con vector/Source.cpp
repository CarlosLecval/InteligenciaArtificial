#include "Busqueda.h"
#include <stdio.h>

using namespace std;

int main(void)
{
	Busqueda p;
	string camino = "";
	int NodoEncontrado = -1;
	int NodoEncontradoInicio = -1;
	int NodoEncontradoFinal = -1;
	if (p.lee_grafo("Ciudades de Mexico.csv"))
	{
		if (p.busqueda_a_lo_ancho("Mexico", "Guadalajara", NodoEncontrado))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por busqueda a lo ancho: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por busqueda a lo ancho\n");

		if (p.busqueda_primero_en_profundidad("Mexico", "Guadalajara", NodoEncontrado))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por busqueda primero en profundidad: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por busqueda primero en profundidad\n");

		if (p.busqueda_profundidad_limitada("Mexico", "Guadalajara", 3, NodoEncontrado))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por busqueda con profundidad limitada: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por busqueda con profundidad limitada\n");

		if (p.busqueda_profundidad_iterativa("Mexico", "Guadalajara", 2, 2, NodoEncontrado))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por busqueda con profundidad iterativa: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por busqueda con profundidad iterativa\n");

		if (p.busqueda_bidireccional("Mexico", "Guadalajara", NodoEncontradoInicio, NodoEncontradoFinal))
		{
			camino = p.devuelve_la_ruta_encontrada_busqueda_bidireccional(NodoEncontradoInicio, NodoEncontradoFinal);
			printf("\nCamino encontrado por busqueda bidireccional: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por busqueda bidireccional\n");

		if (p.busqueda_ascenso_a_la_colina("Mexico", "Guadalajara", NodoEncontrado))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por ascenso a la colina: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por ascenso a la colina\n");

		if (p.busqueda_primero_el_mejor("Mexico", "Guadalajara", NodoEncontrado))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por primero el mejor: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por primero el mejor\n");

		if (p.busqueda_k_beans("Mexico", "Guadalajara", 3, NodoEncontrado))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por k beans: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por k beans\n");

		if (p.busqueda_branch_and_bound("Mexico", "Guadalajara", NodoEncontrado))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por branch and bound: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por branch and bound\n");

		if (p.busqueda_A_estrella("Mexico", "Guadalajara", NodoEncontrado))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por A estrella: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por A estrella\n");
	}
	return 0;
}