#include <iostream>
#include "Grafo.h"
#include "Busqueda.h"
#include <iomanip>
#include "Resultados.h"

using namespace std;

int main()
{
  Grafo g_dirigido("Mexico-USA.csv", true);
  Grafo g_no_dirigido("Mexico-USA.csv", false);
  Busqueda b_grafo_dirigido(g_dirigido);
  Busqueda b_grafo_no_dirigido(g_no_dirigido);
  int costo = 0;
  Resultados r;
  int opcion = -1;
  int nodo_encontrado = -1;
  do {
    cout << "1. Atlacomulco - Oaxaca (No dirigido)" << endl;
    cout << "2. Mexico - Guadalajara (No dirigido)" << endl;
    cout << "3. Aberdeen - Monterrey (No dirigido)" << endl;
    cout << "4. Lakeview - Chicago (Dirigido)" << endl;
    cout << "5. El Paso - Mexicalli (Dirigido)" << endl;
    cout << "6. Salir" << endl;
    cin >> opcion;
    switch (opcion) {
      case 1:
        r.printRutas("Atlacomulco", "Oaxaca", b_grafo_no_dirigido, false, 9, costo);
        break;
      case 2:
        r.printRutasSinProfunidad("Mexico", "Guadalajara", b_grafo_no_dirigido, false, costo);
        break;
      case 3:
        r.printRutasAberdeen("Aberdeen", "Monterrey", b_grafo_no_dirigido, false, 30, costo);
        break;
      case 4:
        r.printRutas("Lakeview", "Chicago", b_grafo_dirigido, true, 40, costo);
        break;
      case 5:
        r.printRutas("El Paso", "Mexicalli", b_grafo_dirigido, true, 40, costo);
        break;
      case 6:
        break;
      default:
        cout << "Opcion invalida" << endl;
        break;
    }
  } while (opcion != 6);
  return 0;
}
