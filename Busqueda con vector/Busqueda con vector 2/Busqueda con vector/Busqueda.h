#pragma once

#include <string>
#include <vector>
#include <stddef.h>

using namespace std;

struct tipo_nodo_informacion
{
	string nombre_del_nodo = "";
	float costo_acumulado = 0.0f;
	int profundidad = 0;
};

struct tipo_nodo_del_arbol
{
	tipo_nodo_informacion contenido;
	int padre = -1;
	vector<int> hijos;
};

struct tipo_enlace_de_grafo
{
	string nodo_1 = "";
	float costo_nodo_1 = 0.0f;
	string nodo_2 = "";
	float costo_nodo_2 = 0.0f;
	float costo_del_enlace = 0.0f;
	float posicion_x_nodo_1 = 0.0f;
	float posicion_y_nodo_1 = 0.0f;
	float posicion_x_nodo_2 = 0.0f;
	float posicion_y_nodo_2 = 0.0f;
};

class Busqueda
{
	public:
		Busqueda();
		~Busqueda();
		bool lee_grafo(string archivo);
		bool busqueda_a_lo_ancho(string nodo_inicio, string nodo_final, int & nodo_encontrado);
		bool bfs(vector<int>& agenda, vector<tipo_nodo_del_arbol>& arbol, string nodo_final, int& nodo_encontrado);
		bool dfs(vector<int>& agenda, vector<tipo_nodo_del_arbol>& arbol, string nodo_final, int& nodo_encontrado);
		bool busqueda_primero_en_profundidad(string nodo_inicio, string nodo_final, int& nodo_encontrado);
		bool busqueda_primero_en_profundidad_limitada(string nodo_inicio, string nodo_final, int& nodo_encontrado, int profundidad);
		bool busqueda_primero_en_profundidad_iterativa(string nodo_inicio, string nodo_final, int& nodo_encontrado);
		bool busqueda_bidireccional(string nodo_inicio, string nodo_final, int& nodo_encontrado);
		string devuelve_la_ruta_encontrada(int nodo_encontrado) const;
	
	private:
		vector<tipo_enlace_de_grafo> grafo;
		vector<tipo_nodo_del_arbol> arbol_de_busqueda;
		vector<int> Agenda;

		void devuelve_vecinos_grafo_no_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const;
		bool devuelve_informacion_de_un_vertice_grafo_no_dirigido(string nodo, int nodo_padre, tipo_nodo_informacion& informacion) const;
		void crea_arbol(tipo_nodo_informacion contenido);
		void agrega_hijo_a_un_nodo(int padre, tipo_nodo_informacion contenido);
		bool esta_un_nodo_en_ancestros(const int nodo_origen, string nombre_del_nodo) const;

		bool devuelve_informacion_de_un_vertice_grafo_no_dirigido_busqueda_bidireccional(string nodo, int nodo_padre, tipo_nodo_informacion& informacion, vector<tipo_nodo_del_arbol>& arbol) const;
		void agrega_hijo_a_un_nodo_busqueda_bidireccional(int padre, tipo_nodo_informacion contenido, vector<tipo_nodo_del_arbol>& arbol);
		bool intersecta(vector<tipo_nodo_del_arbol>& arbol_1, vector<tipo_nodo_del_arbol>& arbol_2, int& nodo_1, int& nodo_2);
};

