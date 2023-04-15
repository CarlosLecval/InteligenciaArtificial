#include <iostream>
#include "Grafo.h"
#include "Busqueda.h"

using namespace std;
int main()
{
  Grafo g_dirigido("Mexico-USA.csv", true);
  Grafo g_no_dirigido("Mexico-USA.csv", false);
  Busqueda b_grafo_dirigido(g_dirigido);
  Busqueda b_grafo_no_dirigido(g_no_dirigido);
  int nodo_encontrado, nodo_encontrado_final;
  int opcion;
  int costo;
  string nodo_inicio, nodo_final;
  /*do 
  {
    cout << "Menu de opciones" << endl;
    cout << "1. Busqueda en anchura" << endl;
    cout << "2. Busqueda en profundidad" << endl;
    cout << "3. Busqueda en profundidad limitada" << endl;
    cout << "4. Busqueda en profundidad iterativa" << endl;
    cout << "5. Busqueda bidireccional" << endl;
    cout << "6. Busqueda de ascenso a la colina" << endl;
    cout << "7. Busqueda primero el mejor" << endl;
    cout << "8. Busqueda k-beans" << endl;
    cout << "9. Busqueda Branch and Bound" << endl;
    cout << "10. Busqueda A*" << endl;
    cout << "0 para salir" << endl;
    cin >> opcion;
    switch (opcion)
    {
      case 1:
        cout << "Busqueda en anchura" << endl;
        cout << "Nodo inicio: ";
        cin >> nodo_inicio;
        cout << "Nodo final: ";
        cin >> nodo_final;
        nodo_encontrado = -1;
        if(b.busqueda_a_lo_ancho(nodo_inicio, nodo_final, nodo_encontrado))
        { 
          cout << "Ruta encontrada: " << b.devuelve_la_ruta_encontrada(nodo_encontrado,costo) << endl;
          cout << "Costo: " << costo << endl;
        }
        else
          cout << "No se encontro la ruta" << endl;
        break;
      case 2:
        cout << "Busqueda en profundidad" << endl;
        cout << "Nodo inicio: ";
        cin >> nodo_inicio;
        cout << "Nodo final: ";
        cin >> nodo_final;
        nodo_encontrado = -1;
        if(b.busqueda_primero_en_profundidad(nodo_inicio, nodo_final, nodo_encontrado))
        { 
          cout << "Ruta encontrada: " << b.devuelve_la_ruta_encontrada(nodo_encontrado,costo) << endl;
          cout << "Costo: " << costo << endl;
        }
        else
          cout << "No se encontro la ruta" << endl;
        break;
      case 3:
        cout << "Busqueda en profundidad limitada" << endl;
        cout << "Nodo inicio: ";
        cin >> nodo_inicio;
        cout << "Nodo final: ";
        cin >> nodo_final;
        int profundidad;
        cout << "Profundidad: ";
        cin >> profundidad;
        nodo_encontrado = -1;
        if(b.busqueda_primero_en_profundidad_limitada(nodo_inicio, nodo_final, nodo_encontrado, profundidad))
        { 
          cout << "Ruta encontrada: " << b.devuelve_la_ruta_encontrada(nodo_encontrado,costo) << endl;
          cout << "Costo: " << costo << endl;
        }
        else
          cout << "No se encontro la ruta" << endl;
        break;
      case 4:
        cout << "Busqueda en profundidad iterativa" << endl;
        cout << "Nodo inicio: ";
        cin >> nodo_inicio;
        cout << "Nodo final: ";
        cin >> nodo_final;
        int primera_profundidad, incremento_profundidad;
        cout << "Primera profundidad: ";
        cin >> primera_profundidad;
        cout << "Incremento de profundidad: ";
        cin >> incremento_profundidad;
        nodo_encontrado = -1;
        if(b.busqueda_primero_en_profundidad_iterativa(nodo_inicio, nodo_final, nodo_encontrado, primera_profundidad, incremento_profundidad))
        { 
          cout << "Ruta encontrada: " << b.devuelve_la_ruta_encontrada(nodo_encontrado,costo) << endl;
          cout << "Costo: " << costo << endl;
        }
        else
          cout << "No se encontro la ruta" << endl;
        break;
      case 5:
        cout << "Busqueda bidireccional" << endl;
        cout << "Nodo inicio: ";
        cin >> nodo_inicio;
        cout << "Nodo final: ";
        cin >> nodo_final;
        nodo_encontrado = -1;
        nodo_encontrado_final = -1;
        if(b.busqueda_bidireccional(nodo_inicio, nodo_final, nodo_encontrado, nodo_encontrado_final))
        { 
          cout << "Ruta encontrada: " << b.devuelve_la_ruta_encontrada(nodo_encontrado,costo) << endl;
          cout << "Costo: " << costo << endl;
        }
        else
          cout << "No se encontro la ruta" << endl;
        break;
      case 6:
        cout << "Busqueda de ascenso a la colina" << endl;
        cout << "Nodo inicio: ";
        cin >> nodo_inicio;
        cout << "Nodo final: ";
        cin >> nodo_final;
        nodo_encontrado = -1;
        if(b.busqueda_ascenso_a_la_colina(nodo_inicio, nodo_final, nodo_encontrado))
        { 
          cout << "Ruta encontrada: " << b.devuelve_la_ruta_encontrada(nodo_encontrado,costo) << endl;
          cout << "Costo: " << costo << endl;
        }
        else
          cout << "No se encontro la ruta" << endl;
        break;
      case 7:
        cout << "Busqueda primero el mejor" << endl;
        cout << "Nodo inicio: ";
        cin >> nodo_inicio;
        cout << "Nodo final: ";
        cin >> nodo_final;
        nodo_encontrado = -1;
        if(b.busqueda_primero_el_mejor(nodo_inicio, nodo_final, nodo_encontrado))
        { 
          cout << "Ruta encontrada: " << b.devuelve_la_ruta_encontrada(nodo_encontrado,costo) << endl;
          cout << "Costo: " << costo << endl;
        }
        else
          cout << "No se encontro la ruta" << endl;
        break;
      case 8:
        cout << "Busqueda k-beans" << endl;
        cout << "Nodo inicio: ";
        cin >> nodo_inicio;
        cout << "Nodo final: ";
        cin >> nodo_final;
        int k;
        cout << "K: ";
        cin >> k;
        nodo_encontrado = -1;
        if(b.beam_search(nodo_inicio, nodo_final, nodo_encontrado, k))
        { 
          cout << "Ruta encontrada: " << b.devuelve_la_ruta_encontrada(nodo_encontrado,costo) << endl;
          cout << "Costo: " << costo << endl;
        }
        else
          cout << "No se encontro la ruta" << endl;
        break;
      case 9:
        cout << "Busqueda Branch and Bound" << endl;
        cout << "Nodo inicio: ";
        cin >> nodo_inicio;
        cout << "Nodo final: ";
        cin >> nodo_final;
        nodo_encontrado = -1;
        if(b.branch_and_bound(nodo_inicio, nodo_final, nodo_encontrado))
        { 
          cout << "Ruta encontrada: " << b.devuelve_la_ruta_encontrada(nodo_encontrado,costo) << endl;
          cout << "Costo: " << costo << endl;
        }
        else
          cout << "No se encontro la ruta" << endl;
        break;
      case 10:
        cout << "Busqueda A*" << endl;
        cout << "Nodo inicio: ";
        cin >> nodo_inicio;
        cout << "Nodo final: ";
        cin >> nodo_final;
        nodo_encontrado = -1;
        if(b.busqueda_a_estrella(nodo_inicio, nodo_final, nodo_encontrado))
        { 
          cout << "Ruta encontrada: " << b.devuelve_la_ruta_encontrada(nodo_encontrado,costo) << endl;
          cout << "Costo: " << costo << endl;
        }
        else
          cout << "No se encontro la ruta" << endl;
        break;
      case 0:
        cout << "Saliendo..." << endl;
        break;
      default:
        cout << "Opcion no valida" << endl;
        break;
    }
  } while (opcion != 0);
  return 0;*/
}
