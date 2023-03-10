#include <iostream>
#include "Conversion.h"
using namespace std;

int main()
{
  int opc = 0;
  int num;
  string bin;
  Conversion c;
  do
  {
    cout << "1. Convertir a binario" << endl;
    cout << "2. Convertir a octal" << endl;
    cout << "3. Convertir a hexadecimal" << endl;
    cout << "4. Convertir binario a decimal" << endl;
    cout << "5. Salir" << endl;
    cout << "Ingrese una opcion: ";
    cin >> opc;
    switch (opc)
    {
    case 1:
      cout << "Ingrese un numero: ";
      cin >> num;
      c.ConvertirBinario(num);
      break;
    case 2:
      cout << "Ingrese un numero: ";
      cin >> num;
      c.ConvertirOctal(num);
      break;
    case 3:
      cout << "Ingrese un numero: ";
      cin >> num;
      c.ConvertirHexadecimal(num);
      break;
    case 4:
      cout << "Ingrese un numero binario: ";
      cin >> bin;
      c.ConvertirBinarioDecimal(bin);
      break;
    case 5:
      cout << "Gracias" << endl;
      break;
    default:
      cout << "Opcion incorrecta" << endl;
      break;
    }
  } while (opc != 5);
}
